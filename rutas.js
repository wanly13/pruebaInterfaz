
// ------- Rutas ------- \\

const rutas = require('express').Router();
const calculate = require('./build/Release/calculate');


console.log(calculate.calc());
console.log(calculate.calc2());

const int=5;
// ASignar todas las rutas

rutas.get('/', function (req , res){
    res.json(calculate.calc())
})



rutas.get('/calc2', function (req , res){
    res.json(calculate.calc2())
})

module.exports = rutas ;