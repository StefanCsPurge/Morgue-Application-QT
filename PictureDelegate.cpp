#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>
#include "domain/victim.h"

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QString photo = index.model()->data(index, Qt::EditRole).toString();

	// show a picture only in the 4th column; the other columns remain unchanged
	if (index.column() != 3)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	if (photo.contains("Naked"))
	{
		QPixmap pixMap("repository/deathdank.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("corona"))
	{
		QPixmap pixMap("repository/nigeye.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("Fail"))
	{
		QPixmap pixMap("repository/meme5.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("value"))
	{
		QPixmap pixMap("repository/meme6.jpeg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("Heavy"))
	{
		QPixmap pixMap("repository/youded.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("hanged"))
	{
		QPixmap pixMap("repository/doge.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("NSA&CIA"))
	{
		QPixmap pixMap("repository/stalinlove.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("missing"))
	{
		QPixmap pixMap("repository/xddone.jpeg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("Surprise"))
	{
		QPixmap pixMap("repository/catded.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("Eagle"))
	{
		QPixmap pixMap("repository/meme23.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else {
		QPixmap pixMap("repository/meme4.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}

}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	//// show a picture only in the second column; the other columns remain unchanged
	if (index.column() == 3)
	{
		return QSize(120, 100);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
