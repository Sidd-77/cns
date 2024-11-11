const WebSocket = require('ws');

// Create WebSocket server on port 8080
const wss = new WebSocket.Server({ port: 8080 });

// Define the prime `P` and base `G` for Diffie-Hellman using BigInt
const P = BigInt(23); // Public prime
const G = BigInt(9);  // Public base

// Server's private key (Bob) as BigInt
const serverPrivateKey = BigInt(67); // b = 3

// Compute server's public key (y = G^b mod P) using BigInt
const serverPublicKey = G ** serverPrivateKey % P;

console.log("Server Public Key:", serverPublicKey.toString());
console.log("Server Private Key:", serverPrivateKey.toString());

wss.on('connection', (ws) => {
    console.log('Client connected!');

    // Send server's public key to the client
    ws.send(JSON.stringify({ type: 'publicKey', publicKey: serverPublicKey.toString(), P: P.toString(), G: G.toString() }));

    // Listen for the client's public key
    ws.on('message', (message) => {
        const { type, publicKey: clientPublicKeyStr } = JSON.parse(message);
        const clientPublicKey = BigInt(clientPublicKeyStr); // Convert to BigInt

        if (type === 'publicKey') {
            console.log('Received Client Public Key:', clientPublicKey.toString());

            // Compute shared secret (ka = x^b mod P) where `x` is the client's public key
            const sharedSecret = clientPublicKey ** serverPrivateKey % P;
            console.log('Server Shared Secret:', sharedSecret.toString());

            // Send the shared secret back to the client for verification (optional)
            // ws.send(JSON.stringify({ type: 'sharedSecret', sharedSecret: sharedSecret.toString() }));
        }
    });
});

console.log('WebSocket server started on ws://localhost:8080');
