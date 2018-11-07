IDENTIFICADOR [a-zA-Z][a-zA-Z0-9_]*
INTEIRO       (+|-)?[0-9]+
TIPOS         (caractere|inteiro|nenhum)
PARAMETROS    {TIPOS}" "{IDENTIFICADOR}((","|", "){TIPOS}" "{IDENTIFICADOR})*
PARAMETROS_C  ({IDENTIFICADOR}|{INTEIRO})((","|", ")({IDENTIFICADOR}|{INTEIRO})*

VARIAVEIS     {TIPOS}" "(("*"|"* ")?){IDENTIFICADOR}((","|", ")(("*"|"* ")?){IDENTIFICADOR})*";"
PROTOTIPOS    {TIPOS}" "(("*"|"* ")?){IDENTIFICADOR}"("{PARAMETROS}?")"((","|", ")(("*"|"* ")?){IDENTIFICADOR}"("{PARAMETROS}?")")*";"
CHAMADA       {IDENTIFICADOR}"("{PARAMETROS_C}?")"
OPERACAO      ((("*"|"&")?){IDENTIFICADOR}|{INTEIRO}|{CHAMADA})("+"|"-"|"/"|"*"|"&&"|"||"|"%")((("*"|"&")?){IDENTIFICADOR}|{INTEIRO}|{CHAMADA})((("+"|"-"|"/"|"*"|"&&"|"||"|"%")((("*"|"&")?){IDENTIFICADOR}|{INTEIRO}|{CHAMADA}))*)
CONDICAO      ({IDENTIFICADOR}|{INTEIRO}|{OPERACAO})

ATRIBUICAO    ("*"?){IDENTIFICADOR}("=")((("*"|"&")?){IDENTIFICADOR}|{INTEIRO}|(("*")?){CHAMADA}|{OPERACAO}|(("*"|"&")?)"("{OPERACAO}")")";"

%%

{VARIAVEIS}  printf("acerto");
{PROTOTIPOS} printf("acerto");

%%
