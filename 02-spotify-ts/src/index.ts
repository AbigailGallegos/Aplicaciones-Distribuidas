// src/index.ts

import { SpotifyService } from './spotifyService';
import express from 'express';
import path from 'path'; // Importa el módulo 'path' para trabajar con rutas de archivos
import hbs from 'hbs';

const clientId = 'CLIENT ID';
const clientSecret = 'CLIET SECRET';

const spotifyService = new SpotifyService(clientId, clientSecret);
const app = express();
const port = 8888; // Puerto en el que se ejecutará el servidor

// Configura HBS como motor de vistas
app.set('view engine', 'hbs');
app.set('views', path.join(__dirname, 'views')); // Establece la ubicación de las vistas

// Define una ruta para renderizar la página con HBS
app.get('/callback', async (req, res) => {
  try {
    const playlists = await spotifyService.getPlaylists();
    //console.log('nombre de usuario: '+  playlists.owner.display_name)
    // Renderiza la plantilla 'index.hbs' y pasa los datos obtenidos a la plantilla
    res.render('index', { playlists });
  } catch (error) {
    console.error('Error:', error);
  }
});

// Inicia el servidor en el puerto especificado.
app.listen(port, () => {
  console.log(`Servidor web en ejecución en http://localhost:${port}`);
});
