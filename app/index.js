'use strict';
import './style.scss';
import Counter from './counter.wasm';

// globals
let COUNTER;

function main() {
  insertCounterGUI();
  loadCounterWasm();
}

function _count() {
  if (COUNTER) {
    document.getElementById('counter').innerHTML = COUNTER.exports._count();
  }
}

function insertCounterGUI() {
  // Insert Counter & Global method for UI
  document.querySelector('#app').insertAdjacentHTML('afterbegin', '<button id="count">Click me</button><div>Count: <span id="counter"></span></div>');
  const count = document.getElementById('count');
  count.addEventListener('click', _count);
}

function loadCounterWasm() {
  const wasmHelloWorld = () => {
    COUNTER = new Counter({
      'env': {
        'memoryBase': 0,
        'tableBase': 0,
        'memory': new WebAssembly.Memory({initial: 256}),
        'table': new WebAssembly.Table({initial: 0, element: 'anyfunc'})
      }
    });
    // console.log("count function result is : " + COUNTER.exports._count());
  };
  window.onload = wasmHelloWorld;
}


main();