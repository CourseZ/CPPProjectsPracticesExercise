#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Book
{
	char ISBN[255];
	char Ten[255];
	int SoTrang;
	char TacGia[255];
};
void NhapSach(Book &b)  //truyen tham chieu (dia chi)
{
	cout<<"Nhap ISBN: ";
	gets(b.ISBN);
	cout<<"Nhap ten sach: ";
	gets(b.Ten);
	cout<<"Nhap so trang: ";
	cin>>b.SoTrang;
	cout<<"Nhap ten tac gia: ";
	cin.ignore();
	gets(b.TacGia);
	
}
void NhapDSSach(Book dsSach[], int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"Nhap sach thu "<<i+1<<endl;
		NhapSach(dsSach[i]);
	}
}
void XuatSach(Book b)
{
	cout<<b.ISBN<<" | "<<b.Ten<<" | "<<b.SoTrang<<" | "<<b.TacGia<<endl;
}
void XuatDanhSach(Book dsSach[], int n)
{
	for(int i=0;i<n;i++)
	{
		XuatSach(dsSach[i]);
	}
}
void LuuFile(Book dsSach[], int n)
{
	ofstream outfile("csdl.txt", ofstream::binary);
	for(int i=0;i<n;i++)
	{
		Book b=dsSach[i];
		outfile.write((char*)&b,sizeof(Book));
	}
	outfile.close();
}
void DocFile(Book dsSach[], int &n)
{
	ifstream infile("csdl.txt", ifstream::binary);
	infile.seekg(0,infile.end);
	long size=infile.tellg();
	infile.seekg(0);
	n=size/sizeof(Book);
	for(int i=0;i<n;i++)
	{
		Book b;
		infile.read((char*)&b,sizeof(Book));
		dsSach[i]=b;
	}
	infile.close();
}
void TimSach(Book dsSach[], int n, char *tg)
{
	for(int i=0;i<n;i++)
	{
		Book b=dsSach[i];
		int kq=strcmp(b.TacGia,tg);
		if(kq==0)
		{
			XuatSach(b);
		}
	}
}
void SapXep(Book dsSach[], int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			Book b1=dsSach[i];
			Book b2=dsSach[j];
			if(b1.SoTrang<b2.SoTrang)
			{
				dsSach[i]=b2;
				dsSach[j]=b1;
			}
		}
	}
}
void XuatTop3(Book dsSach[], int n)
{
	int m=n<3?n:3;
	for(int i=0;i<m;i++)
	{
		XuatSach(dsSach[i]);
	}
}
int main(int argc, char** argv) {
//	int n=20;
//	Book dsSach[n];
//	NhapDSSach(dsSach,n);
//	cout<<"Danh sach SACH vua nhap la: \n";
//	XuatDanhSach(dsSach,n);
//	LuuFile(dsSach,n);

	int max=1000;
	Book dsSach[max];
	int n;
	DocFile(dsSach,n);
	XuatDanhSach(dsSach,n);
	cout<<"Nhap tac gia: ";
	char tg[255];
	gets(tg);
	TimSach(dsSach,n,tg);
	SapXep(dsSach,n);
	cout<<"\nDanh sach SACH sau khi sap xep giam dan so trang: \n";
	XuatDanhSach(dsSach,n);
	cout<<"\nTop 3 sach co nhieu Trang nhat: \n";
	XuatTop3(dsSach,n);
	return 0;
}
