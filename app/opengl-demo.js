import Module from './wasm/module.js'

export class OpenGLDemo {

  module;

  constructor() {
    this.insertCanvas();
    this.loadDemoWasm();
  }

  /**
   * Insert the canvas with id 'canvas' for GLFW to pick up
   */
  insertCanvas() {
    document.querySelector('#app').insertAdjacentHTML('afterend', '<div id="opengl-demo"><canvas id="canvas"></canvas></div>');
  }

  loadDemoWasm() {
    this.module = Module({
      wasmBinaryFile: '/wasm/module.wasm',
      canvas: document.getElementById('canvas')
    });
  }

}

