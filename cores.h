#define printfColor(cor, msg) printf("%s%s%s", cor, msg, RESET)
#define printfSColor(estilo, cor, msg) printf("%s%s%s%s", estilo, cor, msg, RESET)

#define RESET  "\x1b[0m"

//Background (cores de fundo)
#define PRETO_BACKGROUND  "\x1b[40m"
#define BRANCO_BACKGROUND  "\x1b[47m"
#define AMARELO_BACKGROUND   "\x1b[43m"
#define AZUL_BACKGROUND       "\x1b[44m"
#define MAGENTA_BACKGROUND    "\x1b[45m"


//Foreground (cores para textos)
#define PRETO_FOREGROUND   "\x1b[30m"
#define BRANCO_FOREGROUND    "\x1b[37m"
#define VERDE_FOREGROUND  "\x1b[32m"
#define VERMELHO_FOREGROUND  "\x1b[31m"
#define AMARELO_FOREGROUND    "\x1b[33m"
#define AZUL_FOREGROUND      "\x1b[34m"
#define CIANO_FOREGROUND     "\x1b[36m"

#define COR_PECAS "\x1b[33m" //Amarelo/Yellow
#define DESTAQUE "\x1b[46m" //Ciano/Cyan

// Estilos/Styles
#define NEGRITO       "\x1b[1m"
#define SUBLINHADO    "\x1b[4m"