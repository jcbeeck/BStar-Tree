/*
* @author  Oscar Cuadros Linares and Jan Beeck
* @version 1.0
* @since   April-2005
*/

// ArbolBAsterisco.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<math.h>
#include<stdlib.h>
#include<iostream.h>
#include<conio.h>

//#include "thread.hpp"

//Poner el enum para overflow y underflow
//el formato es enum tipo{a=2,b,c}

/**
	@file Clase BAsterTree
*/

/**
* @brief Clase Datos
* Esta clase template contiene el dato y la llave que forman parte de el Arbol B*

*/
template<typename T>
class CDato
{
	public:
		T Dato; /** @param Parametro que contiene une dato de el B* Tree*/
		long m_lLLave; /**@param Este parametro contiene informacion importante
						para acceder a datos relacionados con el buscado*/
		CDato(){}
		CDato(T Dato , int m_lLLave);
		CDato(T Dato);
		/**Sobrecarga de opradores "==" , ">" y "<"*/
		bool operator ==( CDato<T> & A);
		bool operator <( CDato<T> & A);
		bool operator >( CDato<T> & A);
		~CDato(){}


};
template<typename T>
CDato<T>::CDato(T Dato, int m_lLLave)
{
	this->Dato=Dato;
	this->m_lLlave=m_lLLave;
}

template<typename T>
CDato<T>::CDato(T Dato)
{
	this->Dato=Dato;
	long random_number = rand();
	this->m_lLlave=random_number;
}

template<typename T>
bool CDato<T>::operator ==(CDato<T> &A)
{
	return Dato==A.Dato;
}
template<typename T>
bool CDato<T>::operator <(CDato<T> &A)
{
	return Dato<A.Dato;
}
template<typename T>
bool CDato<T>::operator >(CDato<T> &A)
{
	return Dato>A.Dato;
}


//***********************************************************************



/**
	@brief Clase Pagina
	Esta clase contiene un array tipo CDatos y un array de punteros a CPagina
	que son los hijos
 */
template<typename T>
class CPagina
{
	public:
		CDato<T> *m_pDatos; /**@param Array dinámico de Datos */
		int m_iLong; /**@param Longitud del array de datos de la pagina */
		CPagina<T> **m_ppHijos;/**@param Array de punteros a los hijos*/
		CPagina<T> *m_pPadre; /**@param Puntero al padre */
		int m_iPosPadre; /**@param Posicion de la Pagina en el array de hijos del Padre */
		CPagina(int m_iLong);
		CPagina(){}
		~CPagina(){}

};
template<typename T>
CPagina<T>::CPagina(int m_iLong)
{
	this->m_iLong=m_iLong;
	m_iPosPadre=0;
	m_pPadre=0;
	m_pDatos=new CDato<T>[m_iLong+1];
	m_ppHijos=new CPagina<T>*[m_iLong+2];
	for(int i=0;i<m_iLong+1;i++)
		m_pDatos[i].Dato=0;
		m_pDatos[i].m_lLLave=0;
	for(i=0;i<m_iLong+2;i++)
		m_ppHijos[i]=0;

}

//************************************************************************
/** Clase principal en donde de encuentran la raiz y las funciones
	que permitem manipular el arbol	
 */
template<typename T>
class CBAsterisco //:public Win32Thread
{
	private:
		CPagina<T> *m_pRaiz;/** @param Puntero a la raiz del arbol*/
		int m_iIndice; /** @param Es el indice del Árbol*/
	public:
		/**Clase miembro de CBasterisco<T> que me permite recorrer el árbol */
		class m_cIterador
		{
			public:
			//CDato<T> *Dato;
			CPagina<T> *Pagina;
			int Pos;
			m_cIterador(){}
			/**Sobrecarga del operrador ++ para recorrer el árbol en orden*/
			m_cIterador operator ++(int)
			{
				
				//caso hoja
				T Temp;
				if(Pagina->m_ppHijos[0]==0)
				{
					if(Pos<Pagina->m_iLong)
					{
						if(Pagina->m_pDatos[Pos+1].Dato!=0)
						{
							Pos++;
							return *this;
						}
					}
					
				
				
				Temp=Pagina->m_pDatos[Pos].Dato;
				Pagina=Pagina->m_pPadre;
				int i=0;
				while(Pagina->m_pDatos[i].Dato < Temp)
				{
					if(i==Pagina->m_iLong-1)
					{
						i=0;
						Pagina=Pagina->m_pPadre;
					}
					else if(Pagina->m_pDatos[i+1].Dato==0)
					{
						i=0;
						Pagina=Pagina->m_pPadre;
					}
					else
						i++;
					
				}
					
					Pos=i;
					return *this;
				}
				else if(Pagina->m_ppHijos[0]!=0)
				{
					Pagina=Pagina->m_ppHijos[Pos+1];
					while(Pagina->m_ppHijos[0]!=0)
					{
						Pagina=Pagina->m_ppHijos[0];
					}
					Pos=0;
					return *this;
				}
				return *this;
				

			}
			bool operator!=(m_cIterador & A)
			{
				if(Pagina!=A.Pagina)
					return 1;
				else if(Pagina->m_pDatos[Pos]==A.Pagina->m_pDatos[Pos])
					return 0;
				return 1;
					

			}
			
		};
		
		CBAsterisco(int m_iIndice);
		CBAsterisco(); //: Win32Thread() {}
		/**función que retorna un m_cIterator conteniendo al menor de los elementos  */
		m_cIterador Inicio();
		/**Función que retorna el ultimo  elemento del árbol*/
		m_cIterador Fin();
		/**Función booleana de busqueda binaria que indica si un dato existe en el arbol, donde esta o donde deberia estar*/
		bool Buscar(CPagina<T> **&ppPag, CPagina<T> **&ppPad, int &iPos,CDato<T> Dato);
		/**Función booleana que indica si una pagina es hoja*/
		bool Hoja(CPagina<T> **ppPag);
		/**Función que inserta un dato en el arbol*/
		void Insertar(CDato<T> Dato);
		/**Función que inserta un dato en una hoja*/
		void InsertarHoja(CPagina<T> **ppPag, CDato<T> Dato);
		/**Función que intercambia dos elementos de un vector */
		void Intercambiar(int iPos1, int iPos2, CPagina<T> **ppPag );
		/**Función que calcula en numero menor de elemntos que debe tener una página*/
		int Menor(int Indice);
		/**Función que indica si en una página existe algún tipo de violación*/
		int Violacion(CPagina<T>**ppPag);
		/**Función que indica si se puede rotar o partir*/
		int Solucion(CPagina<T> **ppPag, int &PosHer);
		/**Función Partir una pagina que está en overflow*/
		void Partir(CPagina<T> **ppPag, int PosHer);
		/**Función que imprime en pantalla los datos de una pagina */
		void MostrarHoja(CPagina<T> **ppPag);
		/**Funcion que rota los datos a la derecha o izquierda*/
		void Rotar(CPagina<T> **ppPag, int PosHer);
		/**Funcion contar los Datos de un pagina*/
		int Contar(CPagina<T> **ppPag);
		/**Función que es llamada por la función partir en caso de que se tenga que partir la raiz*/
		void PartirRaiz(CPagina<T> **ppPag, int PosHer);
		/**Función que pertenece a la funcion partir y parte los hijos hacia la derecha*/
		void PartirHijosDerecha(CPagina<T> **ppPag,int  PosHer);
		/**Función que pertenece a la funcion partir y parte los hijos hacia la izquierda*/
		void PartirHijosIzquierda(CPagina<T> **ppPag,int  PosHer);
		~CBAsterisco(){}
};
template<typename T>
CBAsterisco<T>::CBAsterisco(int m_iIndice)
{
	m_pRaiz=0;
	this->m_iIndice=m_iIndice;
}
template<typename T>
bool CBAsterisco<T>::Buscar(CPagina<T> **&ppPag, CPagina<T> **&ppPad,int &iPos, CDato<T> Dato)
{
	ppPag=&(m_pRaiz);
	ppPad=&(m_pRaiz);
	CDato<T> NUL;
	NUL.Dato=0;
	NUL.m_lLLave=0;
	while(*ppPag)
	{	
		for(int i=0;i<=(*ppPag)->m_iLong;i++)
		{
			if((*ppPag)->m_pDatos[i]==Dato)
				return 1;
			if((*ppPag)->m_pDatos[i]>Dato)	
			{
				if(Hoja(ppPag)==0)
				{
					ppPag=&(*ppPag)->m_ppHijos[i];
					break;
				}
				else
					return 0;
			}
			else if((*ppPag)->m_pDatos[i]==NUL) //-->Si entra el dato de entrada es mayor
			{
				if((*ppPag)->m_ppHijos[i]==0)
					return 0;
				else
				{
					ppPag=&(*ppPag)->m_ppHijos[i];
					break;
				}
			}				
		}
	}
	return 0;
} 
template<typename T>
bool CBAsterisco<T>::Hoja(CPagina<T> **ppPag)
{
	if((*ppPag)->m_ppHijos[0]==0)
		return 1; //Hoja
	else
		return 0; //No hoja
}
template<typename T>
void CBAsterisco<T>::Insertar(CDato<T> Dato)
{
	CPagina<T> **ppPag=0, **ppPad=0;
	int iPos=0;
	if(Buscar(ppPag, ppPad, iPos, Dato))
		return;//El dato ya existe en el árbol
	else
	{
		if((*ppPag)==0)
		{
			(*ppPag)=new CPagina<T>(m_iIndice*2+1);
		}
		InsertarHoja(ppPag, Dato);
		while(Violacion(ppPag)==2)
		{
			int PosHer;
			if(Solucion(ppPag, PosHer)==0)
			{
				Partir(ppPag, PosHer);
			}
			else if(Solucion(ppPag, PosHer)==2)
			{
				Rotar(ppPag, PosHer);
			}
			else if(Solucion(ppPag, PosHer)==1)
			{
				Partir(ppPag, PosHer);
			}

			if((*ppPag)==m_pRaiz)
				break;
			else
				ppPag=&(*ppPag)->m_pPadre;
		}
	}
}

template<typename T>
void CBAsterisco<T>::InsertarHoja(CPagina<T> **ppPag, CDato<T> Dato)
{
	CDato<T> NUL;
	NUL.Dato=0;
	NUL.m_lLLave=0;
	int Pos=0;

	for(int i=0;i<=(*ppPag)->m_iLong;i++)
	{
		if((*ppPag)->m_pDatos[i]>Dato || (*ppPag)->m_pDatos[i]==NUL)
		{
			Pos=i;
			break;
		}		
	}	
	i=0;
	while((*ppPag)->m_pDatos[i].Dato!=0)
	{
		i++;	
	}
	while(Pos<i)
	{
		Intercambiar(i-1,i,ppPag);
		i--;
	}
	(*ppPag)->m_pDatos[Pos]=Dato; //Inserta el dato
	MostrarHoja(ppPag);
}
template<typename T>
void CBAsterisco<T>::Intercambiar(int iPos1, int iPos2, CPagina<T> **ppPag )
{	
	CDato<T> Temp;
	Temp=(*ppPag)->m_pDatos[iPos2];
	(*ppPag)->m_pDatos[iPos2]=(*ppPag)->m_pDatos[iPos1];
	(*ppPag)->m_pDatos[iPos1]=Temp;
}
template<typename T>
int CBAsterisco<T>::Menor(int Indice)
{
	float A,C;
	int B;
	A=Indice*0.66;
	B=Indice*0.66;
	C=A-B;
	if(C>0.5)
		return B+1;
	return B;
}
template<typename T>
int CBAsterisco<T>::Violacion(CPagina<T> **ppPag)
{
	int Cont=0;
	while((*ppPag)->m_pDatos[Cont].Dato!=0)
	{
		Cont++;
	}
	if(Cont<Menor(m_iIndice))
	{
		if((ppPag)==&(m_pRaiz))
			return 1; //OK
		return 0;     //underflow
	}
	if(Cont>=(*ppPag)->m_iLong+1)
		return 2; //overflow
	return 1;
}
template<typename T>
int CBAsterisco<T>::Solucion(CPagina<T> **ppPag, int &PosHer)
{
	if(*ppPag==m_pRaiz)
		return 0; //Partir 
	//Hojas
	CPagina<T> *Temp;
	Temp=(*ppPag)->m_pPadre->m_ppHijos[(*ppPag)->m_iPosPadre+1]; //Derecha
	if(Temp!=0 && (*ppPag)->m_iPosPadre+1 <= m_iIndice)
	{
		if(Temp->m_pDatos[m_iIndice-1].Dato==0)
		{
			PosHer=(*ppPag)->m_iPosPadre+1;
			return 2; //rotar derecha;
		}
	}
	Temp=(*ppPag)->m_pPadre->m_ppHijos[(*ppPag)->m_iPosPadre-1]; //Izquierda
	if(Temp!=0 && (*ppPag)->m_iPosPadre-1>=0)
	{
		if((*ppPag)->m_pPadre->m_ppHijos[(*ppPag)->m_iPosPadre-1]->m_pDatos[m_iIndice-1].Dato==0)
		{
			PosHer=(*ppPag)->m_iPosPadre-1;
			return 2; //rotar izquierda;
		}

	}
	/////////////
	if((*ppPag)->m_iPosPadre-1<0)
	{
		PosHer=(*ppPag)->m_iPosPadre+1;
		return 1;
	}
	else if((*ppPag)->m_iPosPadre+1 > m_iIndice+1 )
	{
		
		PosHer=(*ppPag)->m_iPosPadre-1;
		return 1;
	}
	else if((*ppPag)->m_pPadre->m_ppHijos[(*ppPag)->m_iPosPadre+1]==0)
	{
		PosHer=(*ppPag)->m_iPosPadre-1;
		return 1;
	}
	PosHer=(*ppPag)->m_iPosPadre-1;
	return 1;//Partir Hijos

	
			
}

template<typename T>
void CBAsterisco<T>::Partir(CPagina<T> **ppPag, int PosHer)
{
	if((*ppPag)==m_pRaiz)
	{	
		PartirRaiz(ppPag,PosHer);
		return;
	}
	else if(PosHer>(*ppPag)->m_iPosPadre)
	{
		PartirHijosDerecha(ppPag, PosHer);
		return;
	}
	else if(PosHer<(*ppPag)->m_iPosPadre)
	{
		PartirHijosIzquierda(ppPag, PosHer);
		return;
	}


}
template<typename T >
void CBAsterisco<T>::PartirHijosDerecha(CPagina<T> **ppPag,int  PosHer)
{	
	CPagina<T> *Temp;
	Temp=new CPagina<T>(m_iIndice*2+1);
	//traspaso de Datos
	int j=0;
	for(int i=0;i<=m_iIndice;i++)
	{
		Temp->m_pDatos[j]=(*ppPag)->m_pDatos[i];
		(*ppPag)->m_pDatos[i].Dato=0;
		(*ppPag)->m_pDatos[i].m_lLLave=0;
		j++;
	}
	for(i=0;(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].Dato!=0;i++)
	{
		Temp->m_pDatos[j]=(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i];
		(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].Dato=0;
		(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].m_lLLave=0;
		j++;
	}
	InsertarHoja(&Temp, (*ppPag)->m_pPadre->m_pDatos[PosHer-1]);
	(*ppPag)->m_pPadre->m_pDatos[PosHer-1].Dato=0;
	(*ppPag)->m_pPadre->m_pDatos[PosHer-1].m_lLLave=0;
	i=PosHer;
	while((*ppPag)->m_pPadre->m_pDatos[i].Dato!=0)
	{
		i++;
	}
	while(i>PosHer)
	{
		Intercambiar(PosHer,PosHer-1,&(*ppPag)->m_pPadre);
		i--;
	}
	i=0;
	while((*ppPag)->m_pPadre->m_ppHijos[i]!=0)
	{
		i++;
	}
	while(i>PosHer)
	{
		(*ppPag)->m_pPadre->m_ppHijos[i]=(*ppPag)->m_pPadre->m_ppHijos[i-1];
		(*ppPag)->m_pPadre->m_ppHijos[i-1]=0;
		i--;
	}
	(*ppPag)->m_pPadre->m_ppHijos[PosHer]=new CPagina<T>(m_iIndice);
	(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pPadre=(*ppPag)->m_pPadre;
	(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_iPosPadre=PosHer;
	//meter los datos a las páginas
	i=0;
	j=PosHer-1;
	int k=0;
	while(i<Temp->m_iLong)
	{
		InsertarHoja(&(*ppPag)->m_pPadre->m_ppHijos[j],Temp->m_pDatos[i]);
		k++;
		if(k==Menor(m_iIndice))
		{
			k=0;
			j++;
			i++;
			InsertarHoja(&(*ppPag)->m_pPadre, Temp->m_pDatos[i]);
		}
		//cout<<Temp->m_pDatos[i].Dato<<"dfwfdwf"<<endl;
		i++;
	
	}
	MostrarHoja(&(*ppPag));
	if(Hoja(ppPag))
		return;
	//copiar los hijos en el temporal
	j=0;
	for(i=0;i<=m_iIndice+1;i++)
	{
		Temp->m_ppHijos[j]=(*ppPag)->m_ppHijos[i];
		(*ppPag)->m_ppHijos[i]=0;
		j++;

	}
	for(i=0;i<=m_iIndice;i++)
	{
		Temp->m_ppHijos[j]=(*ppPag)->m_pPadre->m_ppHijos[PosHer+1]->m_ppHijos[i];
		(*ppPag)->m_pPadre->m_ppHijos[PosHer+1]->m_ppHijos[i]=0;
		j++;
	}
	//meter los hijos en las paginas
	i=0;
	j=PosHer-1;
	k=0;
	while(i<=Temp->m_iLong+1)
	{
		(*ppPag)->m_pPadre->m_ppHijos[j]->m_ppHijos[k]=Temp->m_ppHijos[i];
		k++;
		if(k==m_iIndice)
		{
			k=0;
			j++;
		}
		i++;
	}
	

	

	
}
template<typename T >
void CBAsterisco<T>::PartirHijosIzquierda(CPagina<T> **ppPag,int  PosHer)
{
		CPagina<T> *Temp=new CPagina<T>(m_iIndice*2+1);
		//trapasar los hijos al temporal
		int j=0;
		for(int i=0;i<=m_iIndice;i++)
		{
			Temp->m_ppHijos[j]=(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i];
			j++;
		}
		for(i=0;i<=m_iIndice+1;i++)
		{
			Temp->m_ppHijos[j]=(*ppPag)->m_ppHijos[i];		
		}
		//trapasar los datos a un array temporal
		InsertarHoja(&Temp, (*ppPag)->m_pPadre->m_pDatos[PosHer]);
		(*ppPag)->m_pPadre->m_pDatos[PosHer].Dato=0;
		(*ppPag)->m_pPadre->m_pDatos[PosHer].m_lLLave=0;
		i=PosHer;
		while(i<(*ppPag)->m_pPadre->m_iLong)
		{
			(*ppPag)->m_pPadre->m_pDatos[i]=(*ppPag)->m_pPadre->m_pDatos[i+1];
			i++;
		}
		for(i=0;(*ppPag)->m_pDatos[i].Dato>0;i++)
		{
			InsertarHoja(&Temp, (*ppPag)->m_pDatos[i]);
			(*ppPag)->m_pDatos[i].Dato=0;
			(*ppPag)->m_pDatos[i].m_lLLave=0;
		}
		for(i=0;(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].Dato>0;i++)
		{
			InsertarHoja(&Temp,(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i] );
			(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].Dato=0;
			(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].m_lLLave=0;
		}
		CPagina<T> *Nuevo;
		Nuevo=new CPagina<T>(m_iIndice);
		i=PosHer;
		while((*ppPag)->m_pPadre->m_ppHijos[i]!=0)
		{
			i++;
		}
	
		//traladar los hijos para insertar el nuevo
		while(i>PosHer+1)
		{
			
			(*ppPag)->m_pPadre->m_ppHijos[i-1]->m_iPosPadre=i;
			(*ppPag)->m_pPadre->m_ppHijos[i]=(*ppPag)->m_pPadre->m_ppHijos[i-1];
			i--;
		}
		//Insertar nueva pagina
		ppPag=&(*ppPag)->m_pPadre->m_ppHijos[PosHer+2];
		Nuevo->m_pPadre=(*ppPag)->m_pPadre;
		Nuevo->m_iPosPadre=PosHer+2;
		(*ppPag)->m_pPadre->m_ppHijos[PosHer+1]=Nuevo;
		//Insercion de datos en los hijos partidos 
		i=0;
		j=0;
		while(i<Menor(m_iIndice))
		{
			InsertarHoja(&(*ppPag)->m_pPadre->m_ppHijos[PosHer], Temp->m_pDatos[j]);
			if(Temp->m_ppHijos[j]!=0)
			{
				Temp->m_ppHijos[j]->m_pPadre=(*ppPag)->m_pPadre->m_ppHijos[PosHer];
				Temp->m_ppHijos[j]->m_iPosPadre=i;
			}
			(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i]=Temp->m_ppHijos[j];
			i++;
			j++;
		}
		if(Temp->m_ppHijos[j]!=0)
		{
			Temp->m_ppHijos[j]->m_pPadre=(*ppPag)->m_pPadre->m_ppHijos[PosHer];
			Temp->m_ppHijos[j]->m_iPosPadre=i;
		}
		(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i]=Temp->m_ppHijos[j];
		InsertarHoja(&(*ppPag)->m_pPadre, Temp->m_pDatos[j]);
		i=0;
		j++;
		while(i<Menor(m_iIndice))
		{
			InsertarHoja(&(*ppPag)->m_pPadre->m_ppHijos[PosHer+1], Temp->m_pDatos[j]);
			if(Temp->m_ppHijos[j]!=0)
			{
				Temp->m_pPadre=(*ppPag)->m_pPadre->m_ppHijos[PosHer+1];
				Temp->m_iPosPadre=i;
			}
			(*ppPag)->m_pPadre->m_ppHijos[PosHer+1]->m_ppHijos[i]=Temp->m_ppHijos[j];
			i++;
			j++;
		}
		if(Temp->m_ppHijos[j]!=0)
		{
			Temp->m_pPadre=(*ppPag)->m_pPadre->m_ppHijos[PosHer+1];
			Temp->m_iPosPadre=i;
		}
		(*ppPag)->m_pPadre->m_ppHijos[PosHer+1]->m_ppHijos[i]=Temp->m_ppHijos[j];
		InsertarHoja(&(*ppPag)->m_pPadre, Temp->m_pDatos[j]);
		i=0;
		j++;
		while(i<Menor(m_iIndice))
		{
			InsertarHoja(ppPag, Temp->m_pDatos[j]);
			if(Temp->m_ppHijos[j]!=0)
			{
				Temp->m_pPadre=(*ppPag);
				Temp->m_iPosPadre=i;
			}
			(*ppPag)->m_ppHijos[i]=Temp->m_ppHijos[j];
			i++;
			j++;
		}
		if(Temp->m_ppHijos[j]!=0)
		{
			Temp->m_pPadre=(*ppPag);
			Temp->m_iPosPadre=i;
		}
		(*ppPag)->m_ppHijos[i]=Temp->m_ppHijos[j];
		//MostrarHoja(&(*ppPag)->m_pPadre);
		return;
		

		
					
}

template<typename T>
void CBAsterisco<T>::PartirRaiz(CPagina<T> **ppPag, int PosHer)
{
			//crear una copia de la raiz	
			CPagina<T> *Temp;
			Temp=new CPagina<T>(m_iIndice*2+1);
			for(int i=0;i<=(*ppPag)->m_iLong;i++)
			{
				Temp->m_pDatos[i].Dato=(*ppPag)->m_pDatos[i].Dato;
				Temp->m_pDatos[i].m_lLLave=(*ppPag)->m_pDatos[i].m_lLLave;
				(*ppPag)->m_pDatos[i].Dato=0;
				(*ppPag)->m_pDatos[i].m_lLLave=0;
				Temp->m_ppHijos[i]=(*ppPag)->m_ppHijos[i];
				(*ppPag)->m_ppHijos[i]=0;	
				

			}
			Temp->m_ppHijos[i]=(*ppPag)->m_ppHijos[i];
			(*ppPag)->m_ppHijos[i]=0;
			int j=0,k=0;
			for(i=0;i<=(*ppPag)->m_iLong;i++)
			{
				j++;
				if(j==Menor(m_iIndice))
				{
					i++;
					j=0;
					k++;
				}
			}

			for(i=0;i<k;i++)
			{
				(*ppPag)->m_ppHijos[i]=new CPagina<T>(m_iIndice);
				(*ppPag)->m_ppHijos[i]->m_pPadre=(*ppPag);
				(*ppPag)->m_ppHijos[i]->m_iPosPadre=i;
			}
			//Pasar Datos
			k=0;
			j=0;
			int l=0;
			for(i=0;i<=Temp->m_iLong;i++)
			{
				(*ppPag)->m_ppHijos[j]->m_pDatos[k]=Temp->m_pDatos[i];
				k++;
				if(k==Menor(m_iIndice))
				{
					
					k=0;
					j++;
					i++;
					if(i<Temp->m_iLong+1)
						(*ppPag)->m_pDatos[l]=Temp->m_pDatos[i];
					l++;
					
				}

			}
			//Pasar Hijos
			if(Temp->m_ppHijos[0]!=0)
			{
				j=0;
				k=0;
				for( i=0;i<=(*ppPag)->m_iLong+1;i++)
				{
				
					(*m_pRaiz).m_ppHijos[j]->m_ppHijos[k]=Temp->m_ppHijos[i];
					(*m_pRaiz).m_ppHijos[j]->m_ppHijos[k]->m_pPadre=(*m_pRaiz).m_ppHijos[j];
					(*m_pRaiz).m_ppHijos[j]->m_ppHijos[k]->m_iPosPadre=k;
					k++;
					if(k==m_iIndice)
					{
						k=0;
						j++;
					}
				}
			}
			return;		
}

template<typename T>
void CBAsterisco<T>::Rotar(CPagina<T> **ppPag, int PosHer)
{
	//Rotar izquierda
	if(PosHer<(*ppPag)->m_iPosPadre)
	{
		InsertarHoja(&(*ppPag)->m_pPadre->m_ppHijos[PosHer],(*ppPag)->m_pPadre->m_pDatos[PosHer]);
		(*ppPag)->m_pPadre->m_pDatos[PosHer].Dato=0;
		(*ppPag)->m_pPadre->m_pDatos[PosHer].m_lLLave=0;
		InsertarHoja(&(*ppPag)->m_pPadre, (*ppPag)->m_pDatos[0]);
		(*ppPag)->m_pDatos[0].Dato=0;
		(*ppPag)->m_pDatos[0].m_lLLave=0;
		int i=0;
		while((*ppPag)->m_pDatos[i+1].Dato>0)
		{
			Intercambiar(i,i+1,ppPag);
			i++;
		}
		if(Hoja(ppPag))
			return;
		i=0;
		while((*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_pDatos[i].Dato>0)
		{
			i++;
		}
		(*ppPag)->m_ppHijos[0]->m_pPadre=(*ppPag)->m_pPadre->m_ppHijos[PosHer];
		(*ppPag)->m_ppHijos[0]->m_iPosPadre=i;
		(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i]=(*ppPag)->m_ppHijos[0];
		i=0;
		while((*ppPag)->m_ppHijos[i]!=0)
		{
			(*ppPag)->m_ppHijos[i]=(*ppPag)->m_ppHijos[i+1];
			(*ppPag)->m_ppHijos[i+1]=0;
			i++;
		}
		return;
	}


	//Rotar Derecha
	else if(PosHer>(*ppPag)->m_iPosPadre)
	{
		//Pasando datos
		InsertarHoja(&(*ppPag)->m_pPadre->m_ppHijos[PosHer], (*ppPag)->m_pPadre->m_pDatos[PosHer-1]);	
		(*ppPag)->m_pPadre->m_pDatos[PosHer-1]=(*ppPag)->m_pDatos[m_iIndice];
		(*ppPag)->m_pDatos[m_iIndice].Dato=0;
		(*ppPag)->m_pDatos[m_iIndice].m_lLLave;
		MostrarHoja(ppPag);
		//Pasando Hijos
		if(Hoja(ppPag))
			return;
		int i=0;
		while((*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i]!=0)
		{
			i++;
		}
		while(i>0)
		{
			(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i-1]->m_iPosPadre=i;
			(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i]=(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i-1];
			(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[i-1]=0;
			i--;
		}
		(*ppPag)->m_ppHijos[m_iIndice]->m_pPadre=(*ppPag)->m_pPadre->m_ppHijos[PosHer];
		(*ppPag)->m_ppHijos[m_iIndice]->m_iPosPadre=0;
		(*ppPag)->m_pPadre->m_ppHijos[PosHer]->m_ppHijos[0]=(*ppPag)->m_ppHijos[m_iIndice];
		(*ppPag)->m_ppHijos[m_iIndice]=0;
		return;

	}

}
template<typename T>
void CBAsterisco<T>::MostrarHoja(CPagina<T> **ppPag)
{
	if((ppPag)!=0)
	{
		for(int i=0;i<=(*ppPag)->m_iLong;i++)
		{
			if((*ppPag)->m_pDatos[i].Dato!=0)
			cout<<(*ppPag)->m_pDatos[i].Dato<<endl;
		}
	cout<<endl;
	}
}
template<typename T>
int CBAsterisco<T>::Contar(CPagina<T> **ppPag)
{
	int i=0;
	while((*ppPag)->m_pDatos[i].Dato!=0)
	{
		i++;

	}
	return i;
}

template<typename T>
CBAsterisco<T>::m_cIterador CBAsterisco<T>::Inicio()
{
	CBAsterisco<T>::m_cIterador Menor;
	CPagina<T> **ppPag;
	ppPag=&(m_pRaiz);
	while(!Hoja(ppPag))
	{
		ppPag=&(*ppPag)->m_ppHijos[0];
	
		
	}
	//Menor.Dato=&(*ppPag)->m_pDatos[0];
	Menor.Pagina=*ppPag;
	Menor.Pos=0;
	return Menor;
	
}

template<typename T>
CBAsterisco<T>::m_cIterador CBAsterisco<T>::Fin()
{
	CBAsterisco<T>::m_cIterador Mayor;
	CPagina<T> **ppPag;
	ppPag=&(m_pRaiz);
	int i=0;
	while(!Hoja(ppPag))
	{	
		
		i=0;
		while((*ppPag)->m_pDatos[i].Dato!=0)
		{
			i++;
		}
		ppPag=&(*ppPag)->m_ppHijos[i];
				
	}
	i=0;
	while((*ppPag)->m_pDatos[i].Dato!=0)
	{
		i++;
	}

	//Mayor.Dato=&(*ppPag)->m_pDatos[i-1];
	Mayor.Pagina=*ppPag;
	Mayor.Pos=i-1;
	return Mayor;
	
}

///////////////

int main(int argc, char* argv[])
{
	CBAsterisco<int> oA(3);
	CDato<int> D1;
	for(int i=1;i<=30;i++)
	{
		D1.Dato=i;
		//cin>>D1.Dato;
		oA.Insertar(D1);
		
	}
	
/*	CBAsterisco<int>::m_cIterador Iter, a=oA.Fin();
	Iter=oA.Inicio();
	for(;Iter!=oA.Fin();Iter++)
	{
		cout<<Iter.Pagina->m_pDatos[Iter.Pos].Dato<<endl;	
	}
	
*/	
	
	return 0;
	
	getch();
}
