


const express = require('express');
//const port = 3000;
const port = (process.env.port || 3000);

const app = express();

// Configuarar puerto

app.set('port' , port);


// ------- Rutas ------- \\

app.use('/api' , require('./rutas'));

// ------- Configuracion Express ------- \\

app.use((req, res, next) => {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Headers', 'Authorization, X-API-KEY, Origin, X-Requested-With, Content-Type, Accept, Access-Control-Allow-Request-Method');
    res.header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, DELETE');
    res.header('Allow', 'GET, POST, OPTIONS, PUT, DELETE');
    next();
});


// ------- Iniciar ------- \\

app.listen(app.get('port'),(error)=>{
    if(error){
        console.log("Error en iniciar servivor");
    }
    else{
        console.log("Conectado: " + port);
    }
})