# Dating proposal heart

A captive portal using an ESP32.

## Description

Created to make a creative dating proposal using an [ESP32-S3 with TFT Display](https://github.com/Xinyuan-LilyGO/T-Display-S3).

## Setup

The example below uses the names Bob for the boyfriend and Alice for the girlfriend:

```bash
# Replace names
sed -i 's/{{GIRLFRIEND}}/Alice/g' dating_proposal_heart.ino
sed -i 's/{{BOYFRIEND}}/Bob/g' dating_proposal_heart.ino

# Generate QRCode
qrencode -s 15 -o ssid.png "WIFI:T:nopass;S:Bob ❤ Alice;P:;"
```

### Packaging the webpage

> If you want to edit the HTML page that will be served, follow the steps below to package it.

The `index.html` file contains the proposal page code.
To optimize storage and delivery on a rather limited device like the ESP32-S3, which only has 16MB of flash memory, the following steps were taken with the HTML code:

```bash
# Minify the code
curl -s \
    -X POST \
    --data-urlencode "input=$(cat index.html)" \
    https://www.toptal.com/developers/html-minifier/api/raw > index.html

# Escape quotes
sed -i 's/"/\\"/g' index.html

# Unify lines
echo $(tr -d '\n' < index.html) > index.html

# Split into 8192 byte chunks
split -b 8192 index.html

# Add each chunk inside the print function
sed -i -e 's/^/client.print("/; s/$/");/' x*

# Unify the chunks into one file
paste -sd ' ' x* > index.html
rm x*
```

## License

This project is under the MIT license. See the [LICENSE](./LICENSE) file for details.

---

Made with ❤️ by [lsgalves](https://github.com/lsgalves).

