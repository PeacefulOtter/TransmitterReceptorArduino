# define getLength(arr) ( sizeof(arr) / sizeof(arr[0]) )
 
String phrase = "HELLO WORLD";

String tableAlphabet[37] = {
  "A", "B", "C", "D", "E", "F", "G", "H",
  "I", "J", "K", "L", "M", "N", "O", "P",
  "Q", "R", "S", "T", "U", "V", "W", "X",
  "Y", "Z", "0," "1", "2", "3", "4", "5",
  "6", "7", "8", "9"
};
String tableMorse[37] = {
  // A    B       C       D     E     F     G       H
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
  // I    J       K     L       M     N     O       P
  "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
  // Q     R      S     T     U     V       W       X
  "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  // Y      Z       0        1        2         3       4
  "-.--", "--..", ".----", "..---", "...--", "....-", ".....",
  // 5        6       7         8        9   
  "-....", "--...", "---..", "----.", "-----"
};
 
int laser = 13;
 
int dotTime  = 150;
int dashTime = dotTime * 2;
int asterixTime = dotTime * 3;
int slashTime  = dotTime * 4;
 
 
 
 
 
 
// ENCODE
 
// Conversion to morse langage
String convertToMorse( )
{
  String encode = "";
  int index = 1;

  for ( int i = 0; i < phrase.length(); i++ )
  {
    char c = phrase.charAt(i);
    
    if ( (String) c == " " ) 
    {
      encode.concat( "/" );
      continue;
    }
    
    //iterate through tableAlphabet to find the char
    for ( int j = 0; j < (int) getLength( tableAlphabet ); j++ )
    {
      if ( tableAlphabet[ j ] == (String) c )
      {
        encode.concat( tableMorse[ j ] );
      }
    }
    encode.concat( "*" );
    index++;
  }
  return ( encode );
}


 // turn on & off the laser
void exec( int timing )
{
  digitalWrite( laser, HIGH );
  delay( timing );
  digitalWrite( laser, LOW );
}


void sendMorse( String msg )
{

  for ( int i = 0; i < msg.length(); i++ )
  {
    Serial.print( " " );
    Serial.print( msg[i] );
    if ( (String) msg[ i ] == "." )
    {
      exec( dotTime );
    } else if ( (String) msg[ i ] == "-" )
    {
      exec( dashTime );
    } else if ( (String) msg[ i ] == "*" )
    {
      exec( asterixTime );
    } else if ( (String) msg[ i ] == "/" )
    {
      exec( slashTime );
    }
    delay( dotTime );
  }
  
}

 
 
void setup()
{
  pinMode(laser, OUTPUT);
  Serial.begin(9600);

  // ENCODE MAIN
  String code = convertToMorse();
  Serial.print(code);
  Serial.print( "\n" );
  sendMorse( code );
}
 
 
 
void loop()
{
 
}
