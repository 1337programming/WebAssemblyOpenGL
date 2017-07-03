import './style.scss';
import { Counter } from './counter';
import { OpenGLDemo } from "./opengl-demo";
import Module from './wasm/engine.js'

// Get Worker Thread
// const WorkerThread = require('worker-loader!./worker.js');

function main() {
  addHeader();
  const counter = new Counter();
  const demo = new OpenGLDemo();
  let module = Module({wasmBinaryFile: '/wasm/engine.wasm'});
  // const worker = new WorkerThread();
  // handleWorkerThread(worker);
}

function addHeader() {
  document.querySelector('#app').insertAdjacentHTML('beforebegin', '<h1>WASM Demo</h1>');
}

function handleWorkerThread(worker) {
  worker.postMessage({a: 1});
  worker.onmessage = (event) => {
    console.log('main:', event);
  };
}

window.onload = main;
