#include "MainWindow.hpp"
#include <QApplication>
#include "ImgClassifier/ProfileImage.hpp"
#include <iomanip>

int main(int argc, char *argv[])
{
	/*QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();*/
	// float fmin, fmax, favg;
	// Cica 1
	/*std::cout.setf(std::ios::fixed);
	std::cout << "Cica 1\n";
	Mh::ImageWrapper img("/tmp/cica.jpg");
	img = produceSharpnessProfile(img,15,&fmin, &fmax, &favg);
	img.save(Mh::ImageFileType::TIFF,"/tmp/cica_profil.tiff");
	std::cout << "Min: " << std::setprecision(7) << fmin << "\n"
			<< "Max: " << std::setprecision(7)<< fmax << "\n"
			<< "Avg: " << std::setprecision(7)<< favg << "\n";
	std::cout << "Cica 2\n";
	img = Mh::ImageWrapper("/tmp/cica2.jpg");
	img = produceSharpnessProfile(img,15,&fmin, &fmax, &favg);
	img.save(Mh::ImageFileType::TIFF,"/tmp/cica2_profil.tiff");
	std::cout << "Min: " << std::setprecision(7)<< fmin << "\n"
			<< "Max: " << std::setprecision(7)<< fmax << "\n"
			<< "Avg: " << std::setprecision(7)<< favg << "\n";*/

	Mh::ImageWrapper cica3("/tmp/cica3.jpg");
	Mh::ImageWrapper cica4("/tmp/cica4.jpg");
	Mh::ImageWrapper cica5 = sharpnessComposite(cica3,cica4);
	cica5.save(Mh::ImageFileType::JPEG,"/tmp/cica5.jpg");
	return 0;
}
