import tkinter as tk
from PIL import Image, ImageTk
import numpy as np
from ctypes import *

class SoftViewCanvas:
  def __init__(self, window, width, height):
    self.window = window
    self.width = width
    self.height = height
    self.data = np.array([0] * width * height)
    self.img = None
    self.img_label = None
    self.msg_label = None

    self.response = ""
    self.exit = False

    self.lib = cdll.LoadLibrary('./bin/libSoftView-lib.dll')
    self.lib.SV_initialize_canvas(width, height, int("0xFF333333", 0))

    self.update()

  def __del__(self):
    self.lib.SV_delete_canvas()

  def update(self, msg=""):
    self.get_data()
    img = Image.fromarray(self.data, "RGBA")
    self.img = ImageTk.PhotoImage(img)

    if self.img_label:
      self.img_label.configure(image=self.img)
    else:
      self.img_label = tk.Label(self.window, image=self.img)
      self.img_label.pack()

    if self.msg_label:
      self.msg_label.configure(text=msg)
    else:
      self.msg_label = tk.Label(self.window, anchor="w", font=('Roboto 16'), text=msg)
      self.msg_label.pack(fill=tk.X)

  def get_data(self):
    req = self.lib.SV_update_required
    req.argtype = None
    req.restype = c_bool
    res = req()
    if not res:
      pass

    read = self.lib.SV_get_canvas
    read.argtype = None
    read.restype = POINTER(c_uint32 * self.width * self.height)
    data = read().contents
    self.data = np.array(data, dtype=np.uint32)
    self.data.shape = (self.height, self.width)

def create_window(width, height):
  def submit(entry, canvas):
    data = entry.get()

    handle = canv.lib.SV_handle_command
    handle.argtypes = (c_char_p, POINTER(c_char * 1024), POINTER(c_bool))
    handle.restype = None
    prompt = create_string_buffer(bytes(data, 'ascii'))
    response = create_string_buffer(1024)
    exit = c_bool()

    handle(prompt, response, byref(exit))

    msg = response.value
    if (exit.value):
      canv.window.quit()
    if msg:
      msg = msg[:-1]
    entry.delete(0, tk.END)
    canv.update(msg)

  window = tk.Tk()
  window.title("SoftView")
  window.resizable(False, False)

  canv = SoftViewCanvas(window, width, height)

  entry = tk.Entry(window, font=('Roboto 16'))
  entry.pack(fill=tk.X, side=tk.BOTTOM)
  window.bind('<Return>', lambda event: submit(entry, canv))

  return window

if __name__ == '__main__':
  global lib
  window = create_window(800, 600)
  window.mainloop()
