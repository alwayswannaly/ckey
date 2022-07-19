const net = require('net');
const port = 6969;

if (process.pid) {
  console.log('Process ID: ' + process.pid);
}

function execute(command, callback){
  exec(command, (error, stdout, stderr) => {
    callback(stdout, error);
  });
};

const server = net.createServer();
server.listen(port, function() {
  console.log(`Server listening for connection requests on socket localhost:${port}`);
});

cache = {};

server.on('connection', (socket) => {
  socket.on('data', function(chunk) {
    const [command, key, ...value] = chunk.toString().trim().split(' ');
    switch (command) {
      case 'stats': {
        execute(`ps -p ${process.pid} -o %cpu,%mem`, (result) => {
          socket.write(result);
        });
        break;
      }
      case 'set': {
        cache[key] = value.join(' ');
        socket.write('ok');
        break;
      }
      case 'get': {
        if (cache[key]) {
          socket.write(`1${cache[key]}`);
        } else {
          socket.write('0');
        }
        break;
      }
      case 'delete_matched': {
        Object.keys(cache).forEach(_key => {
          if (_key.match(key)) {
            delete cache[_key];
          }
        });
        socket.write('ok');
        break;
      }
      default: {
        break;
      }
    }
  });

  socket.on('end', function() {
    console.log('Closing connection with the client');
  });

  socket.on('error', function(err) {
    console.log(`Error: ${err}`);
  });
});
