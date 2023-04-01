#include "grille.hpp"
#include "piece.hpp"
#include <SFML/System.hpp>
#include<sstream>
#include<iostream>
#include <time.h> 

Grille::Grille()
{
    for(int i=0;i<hauteur;i++)
    {
      for(int j=0;j<largeur;j++)
      {
        grille[i][j]=0;
      }
    }
}
int Grille::clearLine()
{
    int nb_supprime=0;
    int score=0;
    int k=hauteur-1;
    for (int i=hauteur-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<largeur;j++)
        {
            if (grille[i][j]) count++;
            grille[k][j]=grille[i][j];
        }
        if (count<largeur) k--;
        else nb_supprime+=1;
    }
    if (nb_supprime==1) return 40;
    else if (nb_supprime==2) return 100;
    else if (nb_supprime==3) return 300;
    else if (nb_supprime==4) return 1200;
    else return 0;    

}

void Grille::ajoutePiece(Piece piece)
{
    for (int i=0;i<4;i++) 
    {
        grille[piece.tampon[i].y][piece.tampon[i].x]=piece.color;
    }
}

void Grille::eclairTombe()
{
    int i=0;
    int j=0;
    int quantite=4;
    while(quantite>0 && i<hauteur)
    {
        std::cout << i<<j<<"\n ";
        while(j<largeur && quantite>0)
        {
            if(grille[i][j])
            {
                grille[i][j]=0;
                quantite-=1;
            }
            j++;
        }
        j=0;
        i++;
    }
}

void Grille::asteroideTombe()
{
    int r=rand() % 9+ 1;
    int i=0;
    while(!grille[i][r-1]&&!grille[i][r]&&!grille[i][r+1])
    {
        i++;

    }
    grille[i-3][r-1]=1;
    grille[i-3][r]=1;
    grille[i-3][r+1]=1;
    grille[i-1][r-1]=1;
    grille[i-1][r]=1;
    grille[i-1][r+1]=1;
    grille[i-2][r-1]=1;
    grille[i-2][r]=1;
    grille[i-2][r+1]=1;
}

void Grille::suppColonne()
{
    int r=rand() % 11;
    for(int i=0;i<hauteur;i++)
    {
        grille[i][r]=0;
    }
}

void Grille::suppLigne()
{
    int i=0;
    int j=0;
    bool flag=true;
    while( i<hauteur&&flag)
    {
        while(j<largeur&&flag)
        {
            if(grille[i][j])
            {
                flag=false;
            }
            j++;
        }
        j=0;
        i++;
    }
    for(int u=0; u<largeur;u++)
    {
        grille[i][u]=0;
    }
}