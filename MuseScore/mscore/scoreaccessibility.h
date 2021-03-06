//Copyright (C) 2018 Michail Montesatnos <musikviewer@imslp.org>
#ifndef __SCORE_ACCESSIBILITY__
#define __SCORE_ACCESSIBILITY__

#include <QStatusBar>
#include <QAccessible>
#include <QAccessibleWidget>
#include "scoreview.h"

namespace  Ms {
class AccessibleScoreView : public QObject, QAccessibleWidget {
      Q_OBJECT
public:
      AccessibleScoreView(ScoreView* c);
      int childCount() const Q_DECL_OVERRIDE;
      QAccessibleInterface* child(int /*index*/) const Q_DECL_OVERRIDE;
      QAccessibleInterface* parent() const Q_DECL_OVERRIDE;
      QRect rect() const Q_DECL_OVERRIDE;
      QAccessible::Role role() const Q_DECL_OVERRIDE;
      QString text(QAccessible::Text t) const Q_DECL_OVERRIDE;
      QWindow* window() const  Q_DECL_OVERRIDE;
      static QAccessibleInterface* ScoreViewFactory(const QString &classname, QObject *object);
private:
      ScoreView* s;
      };

class ScoreAccessibility : public QObject {
      Q_OBJECT
private:
      static ScoreAccessibility* inst;
      QMainWindow* mainWindow;
      QLabel* statusBarLabel;
      ScoreAccessibility(QMainWindow* statusBar);
      std::pair<int, float>barbeat(Element* e);

public:
      ~ScoreAccessibility();
      void updateAccessibilityInfo();
      void clearAccessibilityInfo();
      static void createInstance(QMainWindow* statusBar);
      static ScoreAccessibility* instance();
      void currentInfoChanged();
      };

}

#endif
