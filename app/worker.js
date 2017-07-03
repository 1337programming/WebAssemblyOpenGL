// Post data to parent thread

/**
 * Sample worker
 * Good for including intense processes
 */
postMessage({foo: 'foo'});

onmessage = (event) => {
  console.log('worker', event);
};

function main() {
}

main();

