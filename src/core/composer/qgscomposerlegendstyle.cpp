/***************************************************************************
                         qgscomposerlegendstyle.cpp
                         ---------------------
    begin                : March 2013
    copyright            : (C) 2013 by Radim Blazek
    email                : radim.blazek@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgscomposerlegendstyle.h"
#include <QFont>
#include <QMap>
#include <QString>
#include <QDomElement>
#include <QDomDocument>
#include <QDomNode>

QgsComposerLegendStyle::QgsComposerLegendStyle()
{
}

QgsComposerLegendStyle::~QgsComposerLegendStyle()
{
}

void QgsComposerLegendStyle::setMargin( double margin ) 
{ 
  mMarginMap[Top] = margin;
  mMarginMap[Bottom] = margin;
  mMarginMap[Left] = margin;
  mMarginMap[Right] = margin;
}

void QgsComposerLegendStyle::writeXML( QString name, QDomElement& elem, QDomDocument & doc ) const
{
  if ( elem.isNull() ) return;

  QDomElement styleElem = doc.createElement( "style" );

  styleElem.setAttribute( "name", name );

  styleElem.setAttribute( "marginTop", QString::number( mMarginMap[Top] ) );
  styleElem.setAttribute( "marginBottom", QString::number( mMarginMap[Bottom] ) );
  styleElem.setAttribute( "marginLeft", QString::number( mMarginMap[Left] ) );
  styleElem.setAttribute( "marginRight", QString::number( mMarginMap[Right] ) );

  styleElem.setAttribute( "font", mFont.toString() );

  elem.appendChild( styleElem );
}

void QgsComposerLegendStyle::readXML( const QDomElement& elem, const QDomDocument& doc ) 
{
  Q_UNUSED( doc );
  if ( elem.isNull() ) return;

  mFont.fromString( elem.attribute( "font" ) );

  mMarginMap[Top] = elem.attribute( "marginTop" ).toDouble();
  mMarginMap[Bottom] = elem.attribute( "marginBottom" ).toDouble();
  mMarginMap[Left] = elem.attribute( "marginLeft" ).toDouble();
  mMarginMap[Right] = elem.attribute( "marginRight" ).toDouble();
}

QString QgsComposerLegendStyle::styleName ( Style s ) 
{
  switch ( s ) 
  {
    case Undefined:
      return "";
    case Hidden:
      return "hidden";
    case Title:
      return "title";
    case Group:
      return "group";
    case Subgroup:
      return "subgroup";
    case Symbol:
      return "symbol";
    case SymbolLabel:
      return "symbolLabel";
  }
  return "";
}

QgsComposerLegendStyle::Style QgsComposerLegendStyle::styleFromName ( QString styleName ) 
{
  if ( styleName == "hidden" ) return Hidden;
  else if ( styleName == "title" ) return Title;
  else if ( styleName == "group" ) return Group;
  else if ( styleName == "subgroup" ) return Subgroup;
  else if ( styleName == "symbol" ) return Symbol;
  else if ( styleName == "symbolLabel" ) return SymbolLabel;
  return Undefined;
}

QString QgsComposerLegendStyle::styleLabel ( Style s ) 
{
  switch ( s ) 
  {
    case Undefined:
      return QObject::tr("Undefined");
    case Hidden:
      return QObject::tr("Hidden");
    case Title:
      return QObject::tr("Title");
    case Group:
      return QObject::tr("Group");
    case Subgroup:
      return QObject::tr("Subgroup");
    case Symbol:
      return QObject::tr("Symbol");
    case SymbolLabel:
      return QObject::tr("Symbol label");
  }
  return "";
}