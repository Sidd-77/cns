const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:8080');

const clientPrivateKey = BigInt(42); // a = 4

ws.on('open', () => {
    console.log('Connected to server!');
});

ws.on('message', (data) => {
    const message = JSON.parse(data);

    if (message.type === 'publicKey') {
        const serverPublicKey = BigInt(message.publicKey);
        const P = BigInt(message.P);
        const G = BigInt(message.G);

        console.log('Received Server Public Key:', serverPublicKey.toString());
        console.log('Prime (P):', P.toString(), 'Base (G):', G.toString());

        const clientPublicKey = G ** clientPrivateKey % P;
        console.log('Client Public Key:', clientPublicKey.toString());

        ws.send(JSON.stringify({ type: 'publicKey', publicKey: clientPublicKey.toString() }));

        const sharedSecret = serverPublicKey ** clientPrivateKey % P;
        console.log('Client Shared Secret:', sharedSecret.toString());
    }

    if (message.type === 'sharedSecret') {
        console.log('Server Shared Secret (verification):', message.sharedSecret);
    }
});
