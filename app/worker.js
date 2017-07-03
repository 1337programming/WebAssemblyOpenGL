import { OpenGLDemo } from './opengl-demo';

// Post data to parent thread
postMessage({foo: 'foo'});

onmessage = (event) => {
  console.log('worker', event);
};

function main() {
  const demo = new OpenGLDemo();
}

main();

