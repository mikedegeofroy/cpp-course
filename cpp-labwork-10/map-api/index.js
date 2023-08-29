const axios = require('axios');
const fs = require('fs').promises;
var asciify = require('asciify-image');
const express = require('express');

const app = express();
const PORT = process.env.PORT || 3000;

var options = {
  color: false,
  fit: 'box',
  format: 'array',
  height: 50
}

app.get('/ascii-map/', async (req, res) => {
  try {
    console.log(req.headers);
    
    const accessToken = 'pk.eyJ1IjoibWlrZWRlZ2VvZnJveSIsImEiOiJja3ZiOGQwc3I0N29uMnVxd2xlbGVyZGQzIn0.11XK5mqIzfLBTfNTYOGDgw';

    const lat = req.headers["lat"];
    const lon = req.headers["lon"];

    const zoom = 11;

    const mapImage = await fetchMapImage(accessToken, lat, lon, zoom);
    await fs.writeFile('map.png', mapImage);


    asciify('map.png', options, function (err, asciified) {
      if (err) throw err;
      let output = "";
      
      for (let i = 0; i < asciified.length; ++i) {
        output += asciified[i].join("") + "\n";
      }

      res.send(output);
    });
  } catch (error) {
    console.error(error);
    res.status(500).send('An error occurred while generating the ASCII map.');
  }
});

app.listen(PORT, () => console.log(`ASCII Map API listening on port ${PORT}`));


async function fetchMapImage(accessToken, lat, lon, zoom = 14) {
  const mapUrl = `https://api.mapbox.com/styles/v1/mikedegeofroy/cli823vi400r701qub8n0hx9c/static/${lon},${lat},${zoom}/1000x1000?access_token=${accessToken}`;

  const response = await axios.get(mapUrl, { responseType: 'arraybuffer' });
  return Buffer.from(response.data, 'binary');
}