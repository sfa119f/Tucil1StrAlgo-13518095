#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
using namespace std;

//Tipe data
typedef struct {
    float X; //absis
    float Y; //ordinat
} TITIK;

//Selektor
#define Absis(P) (P).X      //mengakses absis
#define Ordinat(P) (P).Y    //mengakses ordinat
#define MaxTitik 1000       //max titik yang dapat dibentuk

//Variabel Global
TITIK CH[MaxTitik]; //titik convex-Hull
int nCH;            //jumlah titik convex-Hull
TITIK T[MaxTitik];  //array titik
int n;              //jumlah titik yang akan diproses

short int cekTitik(TITIK T, TITIK T1, TITIK T2){ //cek titik apakah di atas/bawah dr garis yang menghubungkan 2 titik
    int hsl=(Absis(T)-Absis(T1))*(Ordinat(T2)-Ordinat(T1))-(Ordinat(T)-Ordinat(T1))*(Absis(T2)-Absis(T1));
    if(hsl<0) return -1;
    else if(hsl>0) return 1;
    else return 0;
}

void olahTitik(int n){ //untuk menghasilkan titik yang termasuk convex-hull secara brute-force
    bool jh[MaxTitik];  //untuk checking apakah titik tersebut merupakan hasil
    for(int i=0; i<n; i++){
        jh[i]=false;
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int k=0;
            bool left=true, right=true; //menganggap bahwa diatas/dibawah garis tidak ada titik
            while((left || right) && k<n){
                if(k!=i && k!=j){
                    if(cekTitik(T[k],T[i],T[j])==-1) left=false;
                    else if (cekTitik(T[k],T[i],T[j])==1) right=false;
                }
                k++;
            }
            if(left || right){
                jh[i]=true; jh[j]=true;
            }
        }
    }
    nCH = 0;
    for(int i=0; i<n; i++){
        if(jh[i]){
            Absis(CH[nCH])=Absis(T[i]);
            Ordinat(CH[nCH])=Ordinat(T[i]);
            cout<<Absis(T[i])<<" "<<Ordinat(T[i])<<endl;
            nCH++;
        }
    }
}

void mydisplay(){ //menampilkan titik dan convex hull
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 1);
    if(nCH==2){
        glBegin(GL_LINES);
        glVertex2f(Absis(CH[0])*0.1, Ordinat(CH[0])*0.1);
        glVertex2f(Absis(CH[1])*0.1, Ordinat(CH[1])*0.1);
    }
    else{
        glBegin(GL_TRIANGLE_FAN); //buat convex hull
        for(int i=0; i<nCH ; i++){
            glVertex2f(Absis(CH[i])*0.1, Ordinat(CH[i])*0.1);
        }
    }
    glEnd();
    glFlush();
    glPointSize(5);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);     //buat titik
    for(int i=0; i<n; i++){
        glVertex2f(Absis(T[i])*0.1, Ordinat(T[i])*0.1);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    cin>>n;
    while(n<2) cin>>n; 
    for(int i=0; i<n; i++){
        cin>>Absis(T[i])>>Ordinat(T[i]);
    }
    double t1 = clock(); //waktu proses awal
    olahTitik(n);
    double t2 = clock(); //waktu proses berakhir
    cout<<t2-t1<<endl;
    glutInit(&argc,argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Convex Hull");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}