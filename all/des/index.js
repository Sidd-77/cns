const express = require('express');
const bodyParser = require('body-parser');
const crypto = require('crypto');

// Initialize express
const app = express();
const PORT = 3000;

// Use middleware to parse JSON request bodies
app.use(bodyParser.json());
app.use(express.static(__dirname + '/public'));

app.post('/encrypt', (req, res) => {
    const { message, key } = req.body;

    const desKey = crypto.createHash('md5').update(key).digest('hex').substring(0, 8);

    try {
        const cipher = crypto.createCipheriv('des-ecb', desKey, null);
        let encrypted = cipher.update(message, 'utf8', 'base64');
        encrypted += cipher.final('base64');

        res.json({ encryptedMessage: encrypted });
    } catch (error) {
        console.error('Error during encryption:', error);
        res.status(500).json({ error: 'Encryption failed' });
    }
});

app.post('/decrypt', (req, res) => {
    const { encryptedMessage, key } = req.body;

    const desKey = crypto.createHash('md5').update(key).digest('hex').substring(0, 8);

    try {
        const decipher = crypto.createDecipheriv('des-ecb', desKey, null);
        let decrypted = decipher.update(encryptedMessage, 'base64', 'utf8');
        decrypted += decipher.final('utf8');

        res.json({ decryptedMessage: decrypted });
    } catch (error) {
        console.error('Error during decryption:', error);
        res.status(500).json({ error: 'Decryption failed' });
    }
});

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
