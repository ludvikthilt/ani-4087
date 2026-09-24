## Énoncé

Nous fabriquons une clé de signature, notons son emplacement et son mot de passe ailleurs que dans le dépôt, et rendons la commande employée sans le mot de passe.

## Résolution

### Exécution

Nous avons généré la clé de signature Android avec la commande suivante (sans le mot de passe) :

```powershell
 keytool -genkeypair -alias salle -keyalg RSA -keysize 2048 -validity 10950 -keystore salleKeystor.jks -storetype PKCS12
```

La clé est enregistrée dans le fichier `salleKeystore.jks`, à la racine de notre projet. Pour éviter qu'elle soit envoyée dans le dépôt Git, nous l'avons ajoutée au `.gitignore` :

```gitignore
salleKeystore.jks
```

Le fichier de clé reste ainsi uniquement sur notre machine. Le mot de passe, lui, n'est pas indiqué ici : nous l'avons conservé dans un emplacement personnel et sécurisé, séparé du dépôt.

---

> La clé de signature est générée localement et n'est jamais versionnée dans le dépôt.
> Elle est exclue du suivi Git via le `.gitignore`.
> Le mot de passe est conservé séparément, dans un emplacement personnel sécurisé.
