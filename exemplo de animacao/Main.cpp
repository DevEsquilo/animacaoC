#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define ESC    	27

unsigned char *personagem[3];  // define um vetor indefinido para a personagem, o indice deve ser 1 maior que a quantidade de imagens
unsigned char *sombra[3];    // define um vetor indefinido para a personagem, o indice deve ser 1 maior que a quantidade de imagens
int pg = 0; // define pg para alterar entre desenho e visualização

//codigo dado pelo Banin
void PreparaImg(int Tam, unsigned char *Img, unsigned char *Msk) {
  int i;
  unsigned char B, G, R;
  B = Img[24];
  G = Img[25];
  R = Img[26];
  for(i=24; i < Tam; i+=4) {
    if (Img[i]==B and Img[i+1]==G and Img[i+2]==R) {
      Img[i] = 0;
      Img[i+1] = 0;
      Img[i+2] = 0;
      Msk[i] = 255;
      Msk[i+1] = 255;
      Msk[i+2] = 255;
    }
    else {
      Msk[i] = 0;
      Msk[i+1] = 0;
      Msk[i+2] = 0;
    }
  }
}

//codigo dado pelo Banin/comentarios importantes
void img()
{
	int size = imagesize(0, 0, 234,224); // cria a variavel "size" dentro deste void, sendo usada APENAS dentro deste void
    /*
    "variavel a ser definida como tamanho" = imagesize("inicio da imagem em X", "inicio da imagem em Y", "fim da imagem em X", "fim da imagem em Y");
    */

    setvisualpage(15); // faz o usuario ver a pagina 15
    setactivepage(16); // desenha na pagina 16
    /*
    são usadas as paginas 15 e 16 pois são bem distantes, quando o programa atuaizar as paginas durante o jogo, evita de ele ver esse load das imagens
    */

    //primeiro frame do personagem
    readimagefile("personagem.bmp", 0, 0, 234,224); // le a imagem dentro da pasta, (se quiser colocar dentro do outra pasta use "pasta/pernagem.bmp")
    personagem[0] = (unsigned char *)malloc(size); // alocan o vetor de personagem o tamanho da imagem usando size
    sombra[0] = (unsigned char *)malloc(size); //aloca no vetor de sombras o tamanho da imagem usando size
    getimage(0, 0, 234,224, personagem[0]); // pega a imagem do personagem e coloca dentro do indice "0" para a personagem a ser mostrada
    getimage(0, 0, 234,224, sombra[0]); // pega a imagem da sombra e coloca dentro do indicce "0" para ser a sombra da primeira imagem
    PreparaImg(size, personagem[0], sombra[0]); // faz a preparação da imagem jogando no void "PreparaImg" feito pelo banin (retira as cores que n vao ser usadas)
    
    //segundo frame do personagem /////// a partir daqui, eh so trocar os indices para preencher os vetores, eh usado sempre a mesma forma
    readimagefile("personagem1.bmp", 0, 0, 234,224); 
    personagem[1] = (unsigned char *)malloc(size);
    sombra[1] = (unsigned char *)malloc(size);
    getimage(0, 0, 234,224, personagem[1]);
    getimage(0, 0, 234,224, sombra[1]);
    PreparaImg(size, personagem[1], sombra[1]);

    /*
    readimagefile(""imagem em bmp"","inicio da imagem em X", "inicio da imagem em Y", "fim da imagem em X", "fim da imagem em Y");
    "vetor do personagem[indice]" = (unsigned char *)malloc("tamanho da imagem");
    "vetor da sombra[indice]" = (unsigned char *)malloc("tamanho da imagem");
    getimage("inicio da imagem em X", "inicio da imagem em Y", "fim da imagem em X", "fim da imagem em Y", "vetor do personagem[indice]");
    getimage("inicio da imagem em X", "inicio da imagem em Y", "fim da imagem em X", "fim da imagem em Y", "vetor da sombra[indice]");
    PreparaImg("tamanho da imagem","vetor do personagem[indice]", "vetor da sombra[indice]");    
    */

    readimagefile("personagem2.bmp", 0, 0, 234,224); 
    personagem[2] = (unsigned char *)malloc(size);
    sombra[2] = (unsigned char *)malloc(size);
    getimage(0, 0, 234,224, personagem[2]);
    getimage(0, 0, 234,224, sombra[2]);
    PreparaImg(size, personagem[2], sombra[2]);


    cleardevice();// limpa a tela
    
}

int main(){
    initwindow(500,500);  
    setbkcolor(RGB(255,255,255));

    img(); // chama o metodo de imagem, para ler e preparar as imagens para o jogo

    char tecla;
    int i = 0; // variavel criada para controlar a troca de telas




    while(tecla != ESC){
        if(pg == 2)pg = 1;else pg = 2; // explicado na aula do banin, manipula as pg para desenhar e mostrar as coisas na tela
        setactivepage(pg); // desenha numa pagina definida por "pg"
        cleardevice(); // limpa a tela

        // nao esquecer a ordem, precisa necessariamente ser personagem, dps sombra
        putimage(100, 100, personagem[i], AND_PUT); // coloca o desenho do personagem na tela
        putimage(100, 100, sombra[i], OR_PUT); // faz o recorte com a sombra
        if(i == 2)i = 0;else i++; // impede que o programa tente ler uma imagem que n existe, "i" deve ser igual o tamanho de frames

        setvisualpage(pg); // faz o usuario ver a pagina ja desenhada
        delay(80); // faz com q o programa de uma parada para ser visivel aos olhos

        /*
        putimage("posição X da personagem, posição Y da personagem", "vetor onde a imagem esta alocada", "o que o programa deve fazer com a imagem");
        o putimage da sombra deve ter o X e Y igual aos da personagem
        if(i == 2)i = 0;else i++;    i deve ser igual a quantidade de imagens, contando do zero ( como usei 3 imagens, ele vai passar por 0 então 1 então 2 e voltar ao 0)
        */
    }
}
