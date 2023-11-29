%{
  int chars = 0;
  int words = 0;
  int lines = 0;
%}

%%

[^ \t\n\r\f\v]+   { words++;
                    chars += strlen(yytext); }

\n                { chars++;
                    lines++; }

.                 { chars++; }

%%

int main(int argc, char **argv)
{
  yylex();
  printf("Lines:%d Words:%d Chars:%d\n", lines, words, chars);
  return 0;
}
