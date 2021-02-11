#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

bool isBrackets(char ch);
bool isOperator(char ch);
bool isString (char ch);
char* KeywordMu(char string[],int uzunluk);



//hem konsolda yazdırılacak. Hem de text dosyası oluşturulup yazdırılacak.

int main()
{

    int maxIdentifierSize = 20;
    int uzunluk =0;

    char *ptr,ch;


    FILE *dosyaYaz;

    dosyaYaz =  fopen("code.lex.txt","w");


    FILE *dosya;

    if((dosya = fopen("code.psi.txt","r"))== NULL)
    {
        printf("Dosya açılamadı. \n");
        fprintf(dosyaYaz,"Dosya açılamadı. \n");
        exit(0);
    }




    while((ch = fgetc(dosya)) != EOF)
    {
        uzunluk++;
    }

    rewind(dosya);

    ptr = (char*)malloc(uzunluk*sizeof(char));

    if(ptr== NULL)
    {
        printf("Memory tahsis edilemedi. \n");
        fprintf(dosyaYaz,"Memory tahsis edilemedi. \n");
        exit(0);
    }


    int sayac =0; //Bize malloc ile oluşturduğumuz array'in indeks atamalrı için kullanıldı.

    while((ch = fgetc(dosya)) != EOF)
    {
        ptr[sayac] = ch;
        sayac++;
    }


    //Karakterlerden oluşan ptr array'i oluşturduk.

    //  strcasecmp karşılaştırma yaparken kullanılabilir. Case sensitive değildir.

    int indeks;
    for(indeks=0; indeks<uzunluk;indeks++)
    {

        //Bu seçim sıralaması rastegele değildir. Öncelik sırası oluşturulmuştur.
        //String bölümü

        if(ptr[indeks] == '"')
        {
            indeks++;
            int counter = indeks;
            while(ptr[counter] != '"' && counter<uzunluk)
            {
                counter++;
            }
            printf("String Constant : ");
            fprintf(dosyaYaz,"String Constant : ");
            if(counter>= uzunluk)
            {
                printf("String dosya bitiminden once sonlandirilmadi. \n");
                fprintf(dosyaYaz,"String dosya bitiminden once sonlandirilmadi. \n");

            }
            else
            {
                while(ptr[indeks] != '"')
                {
                    printf("%c",ptr[indeks]);
                    fprintf(dosyaYaz,"%c",ptr[indeks]);
                    indeks++;
                }
                printf("\n");
                fprintf(dosyaYaz,"\n");
                continue;

            }
        }

        //Comments Bölümü

        else if((ptr[indeks] == '(' && ptr[indeks+1] == '*'))
        {
            indeks+=2;

            int counter = indeks;
            while(ptr[counter] != '"' && counter<uzunluk)
            {
                counter++;
            }

            if(counter>= uzunluk)
            {
                printf("Comment dosya bitiminden once sonlandirilmadi. \n");
                fprintf(dosyaYaz,"Comment dosya bitiminden once sonlandirilmadi. \n");

            }
            else
            {
                while(ptr[indeks] != '*' && ptr[indeks+1] != ')')
                {
                    indeks++; // Token üretilmiyor. Yorum kısımları *) görene kadar atlanıyor indeks kaydırılarak atlanıyor.
                }
                indeks++; //indeks * işaretinde durduğu için bunu parantez kısmına getiriyoruz.
            }
            continue;



        }

        //Brackets bölümü. Metot kullanılabilrdi fakat okuma kolaylığı açısından tek tek yazmak istenildi.

        else if((ptr[indeks]=='(') || (ptr[indeks]==')') || (ptr[indeks]=='[') || (ptr[indeks]==']') || (ptr[indeks]=='{') || (ptr[indeks]=='}') )
        {
            printf("Bracket Token : ");
            fprintf(dosyaYaz,"Bracket Token : ");

            if(ptr[indeks]=='(')
            {
                printf("LeftPar \n");
                fprintf(dosyaYaz,"LeftPar \n");
            }
            else if(ptr[indeks]==')')
            {
                printf("RightPar \n");
                fprintf(dosyaYaz,"RightPar \n");
            }
            else if(ptr[indeks]=='[')
            {
                printf("LeftSquareBracket \n");
                fprintf(dosyaYaz,"LeftSquareBracket \n");
            }
            else if(ptr[indeks]==']')
            {
                printf("RightSquareBracket \n");
                fprintf(dosyaYaz,"RightSquareBracket \n");
            }
            else if(ptr[indeks]=='{')
            {
                printf("LeftCurlyBracket \n");
                fprintf(dosyaYaz,"LeftCurlyBracket \n");
            }
            else
            {
                printf("RightCurlyBracket \n");
                fprintf(dosyaYaz,"RightCurlyBracket \n");
            }
            continue;
        }

        //Operators kısmı. Brackets bölümü kopyalanıp düzenlenmiştir.

        else if((ptr[indeks] == '+') || (ptr[indeks] == '-') || (ptr[indeks] == '*') || (ptr[indeks] == '/') ||
                (ptr[indeks] == ':'))
        {
            printf("Operator Token : ");
            fprintf(dosyaYaz,"Operator Token : ");

            if(ptr[indeks]=='+' && ptr[indeks+1] != '+')
            {
                printf("+ \n");
                fprintf(dosyaYaz,"+ \n");
            }
            else if(ptr[indeks]=='-' && ptr[indeks+1] != '-')
            {
                printf("- \n");
                fprintf(dosyaYaz,"- \n");
            }
            else if(ptr[indeks]=='*')
            {
                printf("* \n");
                fprintf(dosyaYaz,"* \n");
            }
            else if(ptr[indeks]=='/')
            {
                printf("/ \n");
                fprintf(dosyaYaz,"/ \n");
            }
            else if(ptr[indeks]=='+' && ptr[indeks+1] =='+')
            {
                printf("++ \n");
                fprintf(dosyaYaz,"++ \n");
                indeks++; //İki basamak yazdırıldığı için indeks bir tane daha kaydırılıyor.
            }
            else if(ptr[indeks]=='-' && ptr[indeks+1] =='-')
            {
                printf("-- \n");
                fprintf(dosyaYaz,"-- \n");
                indeks++;
            }
            else
            {
                printf(":= \n");
                fprintf(dosyaYaz,":= \n");
                indeks++;
            }
            continue;


        }

        //Numbers Bölümü

        else if(ptr[indeks]=='0' || ptr[indeks]=='1' || ptr[indeks]=='2' || ptr[indeks]=='3' || ptr[indeks]=='4' || ptr[indeks]=='5' ||
                ptr[indeks]=='6' || ptr[indeks]=='7' || ptr[indeks]=='8' || ptr[indeks]=='9')
        {
            int counter =0;
            int counter2 = indeks;
            while(ptr[counter2]=='0' || ptr[counter2]=='1' || ptr[counter2]=='2' || ptr[counter2]=='3' || ptr[counter2]=='4' || ptr[counter2]=='5' ||
                ptr[counter2]=='6' || ptr[counter2]=='7' || ptr[counter2]=='8' || ptr[counter2]=='9')
            {
                counter++;
                counter2++;
            }

            printf("Integer Token : ");
            fprintf(dosyaYaz,"Integer Token : ");

            if(counter >10)
            {
                printf("Desteklenmeyen basamak sayisi");
                fprintf(dosyaYaz,"Desteklenmeyen basamak sayisi");
                indeks = indeks + counter; // Rakamları geçip devam etmemiz için.

            }
            else
            {
                while(ptr[indeks]=='0' || ptr[indeks]=='1' || ptr[indeks]=='2' || ptr[indeks]=='3' || ptr[indeks]=='4' || ptr[indeks]=='5' ||
                ptr[indeks]=='6' || ptr[indeks]=='7' || ptr[indeks]=='8' || ptr[indeks]=='9')
                {
                    printf("%c",ptr[indeks]);
                    fprintf(dosyaYaz,"%c",ptr[indeks]);
                    indeks++;
                }
            }
            indeks--;
            printf("\n");
            fprintf(dosyaYaz,"\n");
            continue;


        }

        else if(ptr[indeks] == ';')
        {
            printf("EndOfLine \n");
            fprintf(dosyaYaz,"EndOfLine \n");
        }
        else
        {
            char *subString = (char*)malloc(20* sizeof(char));

            if((ptr[indeks] >= 'a' && ptr[indeks] <='z') || (ptr[indeks] >= 'A' && ptr[indeks] <= 'Z')) //Harf olup olmadığına dair ek bir kontrol.
            {
                subString[0] = ptr[indeks];
                indeks++; // İlk karakter kopyalandı

                int counter = 1; // Substringin 20 karakterden fazla içermemesi için konuldu

                while((ptr[indeks] != ';' && ptr[indeks] != ' ' && isOperator(ptr[indeks]) == false
                && isBrackets(ptr[indeks]) == false && isString(ptr[indeks]) == false ) || ptr[indeks] =='_')
                {
                    if(counter<20) //En fazla 20 karakter alındı.
                    {
                        subString[counter] = ptr[indeks];
                    }
                    counter++; //
                    indeks++;
                }
                indeks--;
                subString[counter] = '\0'; // String son karakteri belirtildi. Memory hataları engellendi.

                if(KeywordMu(subString,counter-1) != '-1')
                {
                    // String döndüren fonksiyon istediğimiz gibi çalışmadı. Biz yine de yorum satırı olarak koymak istedik.

                    //const char* string1 = KeywordMu(subString,counter);
                    printf("Keyword Token : ");
                    fprintf(dosyaYaz,"Keyword Token : ");
                    //printf("%s",&string1);
                    for(int k = 0; k< counter;k++)
                    {
                        subString[k] = tolower(subString[k]);
                    }
                    printf("%s",subString);
                    fprintf(dosyaYaz,"%s",subString);


                }

                else
                {
                    printf("Identifier Token : ");
                    fprintf(dosyaYaz,"Identifier Token : ");
                    if(counter > 20)
                    {
                        printf("Desteklenmeyen Identifier Uzunluğu");
                        fprintf(dosyaYaz,"Desteklenmeyen Identifier Uzunluğu");

                    }
                    else
                    {
                        //Soruda standardize edilmesi istendiği için standardize edilmiştir.

                        for(int k = 0; k< counter;k++)
                        {
                            subString[k] = toupper(subString[k]);
                        }

                        printf("%s",subString);
                        fprintf(dosyaYaz,"%s",subString);

                    }
                }

                printf("\n");
                fprintf(dosyaYaz,"\n");
                free(subString);
            }
        }
    }

    fclose(dosyaYaz);
    fclose(dosya);
    free(ptr);
    return 0;
}

/* Bu metotlar subString oluştururken subString'i nereye kadar alacağımızı belirleyecek olan metotlardır. Yani bir operatöre, brackets'a boşluğa ya da

    endOfLine 'a denk gelinmediği sürece subString oluşturulmaya devam edilecektir. Daha sonrasında bu subString'in keyword olup olmadığına bakılabilir.

    Substring'i else kısmına koymamın sebebi eğer bir karakter bracket, String, Comment, operator, endOfLine ya da integer constant değilse yüksek bir

    ihtimalle identifier ya da keyword'tür (lexical analyzer da kontrol edilmeyen ünlem işareti gibi karakterleri saymazsak, zaten lexical analyzer

    bu tarz karakterleri sınıflandırmadan yok sayıp devam edecektir).


*/
bool isOperator(char ch) // Substring için oluşturulan metot. Bu yüzden operatorlerin ilk karakterlerine bakılması yeterlidir.
{
     if (ch == '+' || ch == '-' || ch == '*' ||
        ch == ':' || ch == '/')
        return (true);
    return (false);
}

bool isBrackets(char ch)
{
    if (ch == '(' || ch == '{' || ch == '[' ||
        ch == ')' || ch == '}' || ch == ']')
        return (true);
    return (false);
}

bool isString (char ch) // String başladığını anlaması için tek bir tırnak işareti görmesi yeterlidir. Comment ler parantez işaretiyle başladığı için
                        // yukarıdaki brackets kontrolü iş görecektir.
{
    if (ch == '"')
        return (true);
    return (false);
}

char* KeywordMu(char stringToken[],int uzunluk)
{
    char keywords[18][10] =
    {

        {'b','r','e','a','k','\0'}, {'c','a','s','e','\0'}, {'c','h','a','r','\0'}, {'c','o','n','s','t','\0'}, {'c','o','n','t','i','n','u','e','\0'},
        {'d','o','\0'}, {'e','l','s','e','\0'}, {'e','n','u','m','\0'}, {'f','l','o','a','t','\0'},
        {'f','o','r','\0'}, {'g','o','t','o','\0'}, {'i','f','\0'}, {'i','n','t','\0'}, {'l','o','n','g','\0'}, {'r','e','c','o','r','d','\0'},
        {'r','e','t','u','r','n','\0'}, {'s','t','a','t','i','c','\0'}, {'w','h','i','l','e','\0'}

    };

    int i;
    for(i=0;i<18;i++)
    {

        if(strncasecmp(keywords[i],stringToken,uzunluk)==0)
        {
            return keywords[i];
        }
    }

    return '-1';

}
