var app = require("http").createServer(handler);
var io = require("socket.io").listen(app);
var fs = require("fs");
var SerialPort = require("serialport").SerialPort;
var sp = new SerialPort("/dev/ttyUSB0");
var S = require("serialport");

var serial_write;

sp.open(function () {
    sp.on('data', function(data) {
        io.sockets.emit('serial', data.toString());
    });
    serial_write = function(data) {
        sp.write(data);
    }
});

app.listen(8080);

function handler (req, res) {
    fs.readFile(__dirname + "/index.html", function(err, data) {
        res.writeHead(200);
        res.end(data);
    });
}

io.sockets.on('connection', function(socket) {
    socket.on('serial', function (data) {
        serial_write(data);
    });
});
