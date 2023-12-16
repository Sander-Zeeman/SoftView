import Module from './libSoftView.js';

Module().then((value) => {
    window.module = value;
    window.module._SV_initialize_canvas(800, 600, 0xff333333);
    module.sander = {};
    module.sander.data = window.module._SV_get_canvas();
    module.sander.canv = new Uint32Array(
        window.module.wasmMemory.buffer,
        module.sander.data,
        800 * 600
    );
});
