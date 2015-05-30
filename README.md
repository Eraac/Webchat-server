# Webchat-server
Chat en ligne via les WebSocket en C++

# Documentation

Le serveur reçoit des JSON et renvoie des JSON.

### Connexion au serveur via un client

Pour se connecter au serveur, il faut initialiser un WebSocket (ws://) sur l'ip du serveur et le port 12345 (modifiable dans le fichier 'settings.ini'). Une fois connecté il faut envoyer au serveur un JSON contenant les clés 'username' et 'password' (voir encodepassword.cpp pour la méthode de hashage).

Le serveur ajoute automatiquement les nouveaux utilisateurs dans la salle "default".

### Envoyer un message

Pour envoyer un message aux utilisateurs connectés, il suffit d'envoyer un JSON avec deux clés : 'message' contenant le message et type contenant la valeur 1 (voir clé 'type').

### Envoyer des commandes

Pour envoyer des commandes au serveur, il suffit d'envoyer un JSON avec au minimum deux clés : 'type' contenant la valeur 6 et le code de la commande (voir clé 'command'). Plus des informations supplémentaire si cela est néccessaire (voir colonne 'info').

### Recevoir un message

Le serveur envoie un JSON avec deux clés : 'username' contenant le nom de l'utilisateur qui a envoyé le message, et 'message' contenant le message.

### Contenu du JSON

#### Clé "type"

| Valeur  | Désignation | Info |
|:-------:|-------------|------|
| 1       | Un utilisateur à envoyer un message | Le message est contenu dans la clé "message" |
| 2       | Une erreur est survénu (voir code erreur) | Le code erreur est contenu dans la clé "code" |
| 3       | Opération réussi avec succès (voir code succès) | Le code de l'opération est contenu dans la clé "code" |
| 4       | Un utilisateur c'est connecté sur le chat | Le nom de l'utilisateur est contenu dans la clé "username" |
| 5       | Un utilisateur c'est déconnecté | Le nom de l'utilisateur est contenu dans la clé "username" et la raison dans "reason" (voir code reason) |
| 6       | Indique au serveur que le message envoyé est une commande (voir code commande) | Le code de la commande est contenu dans "command" |

#### Clé "code" (succès)

| Valeur  | Désignation |
|:-------:|-------------|
| 1       | Mot de passe changé |
| 2       | Vous êtes connecté  |

#### Clé "code" (erreur)

| Valeur  | Désignation |
|:-------:|-------------|
| 1       | Erreur du serveur |
| 2       | Mauvais mot de passe ou compte inexistant  |
| 3       | Commande inconnue  |
| 4       | Le nouveau mot de passe ne peut pas être vide  |
| 5       | Type inconnu  |

#### Clé "command"

| Valeur  | Désignation | Info |
|:-------:|-------------|------|
| 1       | Changer de mot de passe | Le nouveau mot de passe doit-être dans la clé "newPassword" |
| 2       | Changer de salle de chat  | Le nom de la nouvelle salle doit-être dans la clé "newRoom" |

#### Clé "reason"

| Valeur  | Désignation |
|:-------:|-------------|
| 1       | L'utilisateur à rompu la connexion |
| 2       | L'utilisateur à changé de salle |
