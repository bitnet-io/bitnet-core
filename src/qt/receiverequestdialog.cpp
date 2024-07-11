// Copyright (c) 2011-2021 The Bitnet Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/receiverequestdialog.h>
#include <qt/forms/ui_receiverequestdialog.h>

#include <qt/bitnetunits.h>
#include <qt/guiutil.h>
#include <qt/optionsmodel.h>
#include <qt/qrimagewidget.h>
#include <qt/walletmodel.h>

#include <QDialog>
#include <QString>




//for infinite loops
//#include <QThread>
//#include <QDebug>
//#include <QWidget>
//#include <QApplication>
//#include <iostream>
//#include <random>
//#include <string>
//#include <unistd.h>


#include <unistd.h>

#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>



#include <string>
#include <iostream>




#if defined(HAVE_CONFIG_H)
#include <config/bitnet-config.h> /* for USE_QRCODE */
#endif

using namespace std;


ReceiveRequestDialog::ReceiveRequestDialog(QWidget* parent)
    : QDialog(parent, GUIUtil::dialog_flags),
      ui(new Ui::ReceiveRequestDialog)
{
    ui->setupUi(this);
    GUIUtil::handleCloseWindowShortcut(this);
}

ReceiveRequestDialog::~ReceiveRequestDialog()
{
    delete ui;
}

void ReceiveRequestDialog::setModel(WalletModel *_model)
{
   this->model = _model;

//    if (_model)
//        connect(_model->getOptionsModel(), &OptionsModel::displayUnitChanged, this, &ReceiveRequestDialog::updateDisplayUnit);

    // update the display unit if necessary
//    update();
}







void ReceiveRequestDialog::setInfo(const SendCoinsRecipient &_info)
{
//while (1 > 0) {

//    int length = 25;
//    std::string random_string = generateRandomString(length); 
//    QString str = QString::fromLocal8Bit(random_string.c_str());


   QEventLoop *localLoop = new QEventLoop();

    this->info = _info;
//   setWindowTitle(tr("Request payment to %1").arg(info.label.isEmpty() ? info.address : info.label));
    QString uri = GUIUtil::formatBitnetURI(info);

   ui->uri_content->setText("<a href=\"" + uri + "\">" + GUIUtil::HtmlEscape(uri) + "</a>");
   ui->address_content->setText(info.address);


//#ifdef USE_QRCODE

//    if (ui->qr_code->setQR(str, info.address)) {
//        connect(ui->btnSaveAs, &QPushButton::clicked, ui->qr_code, &QRImageWidget::saveImage);
//    } else {
//        ui->btnSaveAs->setEnabled(false);
//    }


//#else
//    ui->btnSaveAs->hide();
//    ui->qr_code->hide();
//	}

//}
//#endif










    if (!info.amount) {
        ui->amount_tag->hide();
        ui->amount_content->hide();
    } // Amount is set in updateDisplayUnit() slot.
    updateDisplayUnit();

//    if (!info.label.isEmpty()) {
  //      ui->label_content->setText(info.label);
 //   } else {
   //     ui->label_tag->hide();
   //     ui->label_content->hide();
   // }

    if (!info.message.isEmpty()) {
        ui->message_content->setText(info.message);
    } else {
        ui->message_tag->hide();
        ui->message_content->hide();
    }

    if (!model->getWalletName().isEmpty()) {
        ui->wallet_content->setText(model->getWalletName());
    } else {
        ui->wallet_tag->hide();
        ui->wallet_content->hide();
    }

//    ui->btnVerify->setVisible(model->wallet().hasExternalSigner());







//    connect(ui->btnVerify, &QPushButton::clicked, [this] {
//        model->displayAddress(info.address.toStdString());
//    });


//        model->displayAddress(info.address.toStdString());

            usleep(100000);

    QTimer::singleShot(200, localLoop, SLOT(quit()));
    localLoop->exec();
    localLoop->deleteLater();



//}

}

void ReceiveRequestDialog::setInfoReal(const SendCoinsRecipient &_info)
{
//while (1 > 0) {
// QEventLoop loop;


   QEventLoop *localLoop = new QEventLoop();

    this->info = _info;
//   setWindowTitle(tr("Request payment to %1").arg(info.label.isEmpty() ? info.address : info.label));

    QString uri = GUIUtil::formatBitnetURI(info);
    ui->uri_content->setText("<a href=\"" + uri + "\">" + GUIUtil::HtmlEscape(uri) + "</a>");
    ui->address_content->setText(info.address);

//    QString uri = QString::fromLocal8Bit(info);


//#ifdef USE_QRCODE

    if (ui->qr_code->setQR(uri, info.address)) {
//        connect(ui->btnSaveAs, &QPushButton::clicked, ui->qr_code, &QRImageWidget::saveImage);
    } else {
//        ui->btnSaveAs->setEnabled(false);
   }

//        connect(ui->btnSaveAs, &QPushButton::clicked, ui->qr_code, &QRImageWidget::saveImage);

//#else
//    ui->btnSaveAs->hide();
//    ui->qr_code->hide();
//	}

//}
//#endif






    if (!info.amount) {
        ui->amount_tag->hide();
        ui->amount_content->hide();
    } // Amount is set in updateDisplayUnit() slot.
    updateDisplayUnit();

//    if (!info.label.isEmpty()) {
 //       ui->label_content->setText(info.label);
 //   } else {
 //       ui->label_tag->hide();
 //       ui->label_content->hide();
 //   }

    if (!info.message.isEmpty()) {
        ui->message_content->setText(info.message);
    } else {
        ui->message_tag->hide();
        ui->message_content->hide();
    }

    if (!model->getWalletName().isEmpty()) {
        ui->wallet_content->setText(model->getWalletName());
    } else {
        ui->wallet_tag->hide();
        ui->wallet_content->hide();
    }

//    ui->btnVerify->setVisible(model->wallet().hasExternalSigner());







//    connect(ui->btnVerify, &QPushButton::clicked, [this] {
//        model->displayAddress(info.address.toStdString());
//    });

          usleep(80000);

    QTimer::singleShot(100, localLoop, SLOT(quit()));
    localLoop->exec();
    localLoop->deleteLater();

//	}


}











void ReceiveRequestDialog::updateDisplayUnit()
{
    if (!model) return;
    ui->amount_content->setText(BitnetUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), info.amount));
}

void ReceiveRequestDialog::on_btnCopyURI_clicked()
{
    GUIUtil::setClipboard(GUIUtil::formatBitnetURI(info));
}

void ReceiveRequestDialog::on_btnCopyAddress_clicked()
{
    GUIUtil::setClipboard(info.address);
}
