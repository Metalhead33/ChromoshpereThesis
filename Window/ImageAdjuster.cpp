#include "ImageAdjuster.hpp"
#include "ui_ImageAdjuster.h"
#include <QFileDialog>
#include <QMessageBox>

ImageAdjuster::ImageAdjuster(Mh::ImageWrapper&& mov, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ImageAdjuster),
	wrap(mov)
{
	ui->setupUi(this);
	ui->ContrastSlider->setMinimum(-100);
	ui->ContrastSlider->setMaximum(100);
	ui->BrightnessSlider->setMinimum(-100);
	ui->BrightnessSlider->setMaximum(100);
	ui->GammaSlider->setMinimum(0);
	ui->GammaSlider->setMaximum(100);
	ui->SharpenSlider->setTickPosition(QSlider::TickPosition::TicksBothSides);
	ui->SharpenSlider->setMinimum(0);
	ui->SharpenSlider->setMaximum(15);
	updatePreview();
	updateImageView();
}

ImageAdjuster::~ImageAdjuster()
{
	delete ui;
}
void ImageAdjuster::updatePreview()
{
	preview = wrap;
	preview.adjustColors(brightness,contrast,gamma,false);
}
void ImageAdjuster::updateImageView()
{
	auto jpEgV = preview.saveToMemory(Mh::ImageFileType::JPEG);
	image.loadFromData(reinterpret_cast<uchar*>(jpEgV.data()),jpEgV.size());
	ui->ImagePreview->setPixmap(image);
	ui->ImagePreview->setScaledContents(true);
}

void ImageAdjuster::on_pushButton_clicked()
{
	updatePreview();
	updateImageView();
}

void ImageAdjuster::on_BrightnessSlider_sliderReleased()
{
	brightness = double(ui->BrightnessSlider->value()) / 100.00;
}

void ImageAdjuster::on_ContrastSlider_sliderReleased()
{
	contrast = double(ui->ContrastSlider->value()) / 100.00;
}

void ImageAdjuster::on_GammaSlider_sliderReleased()
{
	gamma = double(ui->GammaSlider->value()) / 100.00;
}

void ImageAdjuster::on_SharpenSlider_sliderReleased()
{
	sharpen = ui->SharpenSlider->value();
}

void ImageAdjuster::on_PreviewButton_accepted()
{
	try {
	updatePreview();
	auto saveName = QFileDialog::getSaveFileName(this,
		tr("Save Image"), "", tr("JPEG Image Files (*.jpg)"));
	if(!saveName.length()) return;
	auto saveUtf8 = saveName.toStdString();
	if(!preview.save(Mh::ImageFileType::JPEG,saveUtf8.c_str()))
		throw std::runtime_error("Failed to save the image!");
	QMessageBox messageBox;
	messageBox.information(this,"Success!","Successfully saved the image!");
	messageBox.setFixedSize(500,200);
	} catch(const std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(this,"Error",e.what());
		messageBox.setFixedSize(500,200);
	}
}
