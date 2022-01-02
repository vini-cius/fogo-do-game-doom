#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int get_int(fstream& stream, int offset)
{
	stream.seekg(offset);
	int result = 0;
	int base = 1;
	
	for (int i = 0; i < 4; i++)
	{
		result = result + stream.get() * base;
		base = base * 256;
	}
	
	return result;
}

void convertePixel(int& blue, int& green, int& red)
{
	// verificar se algum tom rgb possui valor maior que 200
	// se sim, alterar rgb para 255 ou, caso contrário 0
    if(blue < 200 || red < 200 || green < 200)
    {
    	blue = red = green = 0;
    }
	else
	{
		blue = red = green = 255;
	}
}

void converteImagem(string filename)
{
	// colocar aqui o código para abrir o arquivo e processar a imagem
	fstream stream;
	// Abre como um arquivo binário
	stream.open(filename.c_str(), ios::in | ios::out | ios::binary);
	// pega as dimensões da imagem
	int file_size = get_int(stream, 2); 
	int start = get_int(stream, 10);
	int width = get_int(stream, 18);
	int height = get_int(stream, 22);
	// Verifica se as linhas possuem múltiplo de 4 bytes
	int scanline_size = width * 3;
	int padding = 0;
	if (scanline_size % 4 != 0)
	{
		padding = 4 - scanline_size % 4;
	}
	
	if (file_size != start + (scanline_size + padding) * height)
	{
		cout << "file_size..: " << file_size << endl;
		cout << "start + (scanline_size + padding) * height ...: "
		     << start + (scanline_size + padding) * height << endl;
		cout << "Imagem BMP invalida..." << endl;
		exit(1);
	}
	// ir para o inicio dos pixels da imagem
	stream.seekg(start);
	
	 // processar cada linha da imagem
	 for (int i = 0; i < height; i++)
	 {
         // processar cada pixel da linha
		 for (int j = 0; j < width; j++)
		 {
		 // ir para o inicio do pixel	
		 int pos = stream.tellg();
		 
		 // ler os pixels
		 int blue = stream.get();
		 int green = stream.get();
		 int red = stream.get();
		
		 // converter o pixel
		 convertePixel(blue, green, red);

		 // voltar para o início do pixel
		 stream.seekp(pos);
		
		// gravar o pixel alterado
		 stream.put(blue);
		 stream.put(green);
		 stream.put(red);
		 }
	
	 // pular o padding (enchimento para cada linha ter um 
	 // múltiplo de 4 pixels)
	 stream.seekg(padding, ios::cur);
	 }
	 // fechar o arquivo
	 stream.close();
}


int contaPixelsPretos(string filename){
	int qtd = 0;
	
	// contar os pixels com valor zero para rgb
	fstream stream;
	// Abre como um arquivo binário
	stream.open(filename.c_str(), ios::in | ios::out | ios::binary);
	// pega as dimensões da imagem
	int file_size = get_int(stream, 2); 
	int start = get_int(stream, 10);
	int width = get_int(stream, 18);
	int height = get_int(stream, 22);
	// Verifica se as linhas possuem múltiplo de 4 bytes
	int scanline_size = width * 3;
	int padding = 0;
	if (scanline_size % 4 != 0)
	{
		padding = 4 - scanline_size % 4;
	}
	if (file_size != start + (scanline_size + padding) * height)
	{
		cout << "Imagem BMP invalida..." << endl;
		exit(1);
	}
	// ir para o inicio dos pixels da imagem
	stream.seekg(start);
	
	 // processar cada linha da imagem
	 for (int i = 0; i < height; i++)
	 {
         // processar cada pixel da linha
		 for (int j = 0; j < width; j++)
		 {
		 // ir para o inicio do pixel	
		 int pos = stream.tellg();
		 
		 // ler os pixels
		 int blue = stream.get();
		 int green = stream.get();
		 int red = stream.get();
		
		if (red == 0) qtd++;
		
		 }
	
	 // pular o padding (enchimento para cada linha ter um 
	 // múltiplo de 4 pixels)
	 stream.seekg(padding, ios::cur);
	 }
	 // fechar o arquivo
	 stream.close();

	return qtd;
}


int main()
{
	string filename;
	cout << "Arquivo com um objeto.........:  ";      
	cin >> filename;
	converteImagem(filename);
    int qtdPixels1 = contaPixelsPretos(filename);

	cout << "Arquivo com muitos objetos....:  ";
	cin >> filename;
	converteImagem(filename);
    int qtdPixelsN = contaPixelsPretos(filename);
	float qtdObjetos = math.ceil((float)qtdPixelsN /  (float)qtdPixels1);
	
	cout << "Pelos meus calculos, ha " << qtdObjetos 
	     << " Objetos na imagem." << endl;
	
	 return 0;
 }

