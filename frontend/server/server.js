var express = require('express')
var path = require('path')

var server = express()

server.use(express.static(path.join(__dirname, '..', 'dist')))

server.listen(9000)
console.log('Start softrd-dist server')