#ifndef IMAGEADJUSTER_HPP
#define IMAGEADJUSTER_HPP

#include <QDialog>
#include "../Wrapper/MhImageWrapper.hpp"

namespace Ui {
class ImageAdjuster;
}

class ImageAdjuster : public QDialog
{
	Q_OBJECT

public:
	explicit ImageAdjuster(Mh::ImageWrapper&& mov, QWidget *parent = nullptr);
	~ImageAdjuster();

	void updatePreview();
	void updateImageView();
private slots:
	void on_pushButton_clicked();

	void on_BrightnessSlider_sliderReleased();

	void on_ContrastSlider_sliderReleased();

	void on_GammaSlider_sliderReleased();

	void on_SharpenSlider_sliderReleased();

	void on_PreviewButton_accepted();

private:
	Ui::ImageAdjuster *ui;
	Mh::ImageWrapper wrap;
	Mh::ImageWrapper preview;
	QPixmap image;
	double brightness, contrast, gamma;
	int sharpen;
};

#endif // IMAGEADJUSTER_HPP
