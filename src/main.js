let app = document.getElementById('app');
let ctx = app.getContext('2d');
let wasm = null;

function onEnterPress() {
	const key = window.event.keyCode;
	if (key == 13) {
		const text = document.getElementById('input');
		handle_command(text.value, text.value.length);
		update();
		text.value = '';
	}
}

function decode_cstr(ptr, length) {
	const buffer = wasm.instance.exports.memory.buffer;
	const arr = new Uint8Array(buffer);
	const bytes = new Uint8Array(buffer, ptr, length)
	return new TextDecoder().decode(bytes);
}

function platform_log(msg_ptr, length) {
	const arr = decode_cstr(msg_ptr, length);
	console.log("LOG (", length, "): ", arr);
}

function initialize() {
	width = app.width;
	height = app.height;
	wasm.instance.exports.init(width, height)
}

function handle_command(str, length) {
	let encoder = new TextEncoder();
	let encoded = encoder.encode(str);
	let msg = new Uint8Array(wasm.instance.exports.memory.buffer, 0, encoded.length);
	msg.set(encoded);

	wasm.instance.exports.handle(msg.byteOffset, length);
}

function update() {
	const canvas_ptr = wasm.instance.exports.update();
	const canvas_arr = new Uint8ClampedArray(wasm.instance.exports.memory.buffer, canvas_ptr, app.width * app.height * 4);
	const canvas_data = new ImageData(canvas_arr, app.width, app.height);
	ctx.putImageData(canvas_data, 0, 0);
}

WebAssembly.instantiateStreaming(fetch('../SoftView.wasm'), {
	env: {
		platform_log,
	}
}).then(w => {
	wasm = w;

	let growth = app.width * app.height * 4 / 65536;
	wasm.instance.exports.memory.grow(growth);

	initialize();
	update();
});
