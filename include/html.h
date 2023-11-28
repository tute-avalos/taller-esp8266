
#ifndef __HTML_H__
#define __HTML_H__

const char * indexPageStart = 
"<!DOCTYPE html>"
"<html lang='es'>"
"<head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>LAMPS Control</title>"
"</head>"
"<body>"
  "<h1>Control de Lamparas</h1>"
  "<form action='/cambiar_estado' method='post'>"
  "<p>LED ¿prendido?"
      "<input type='checkbox' name='estado' id='estado'>"
  "</p>"
  "<input type='submit' value='ENVIAR'>"
  "</form>";

const char * estadoLed = 
  "<p>LED {s}</p>";

const char * indexPageEnd = 
  "<a href='/toggle'>invertir LED</a>"
"</body>"
"</html>";

#endif // __HTML_H__
