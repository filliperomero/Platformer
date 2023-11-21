// Copyright Fillipe Romero

#include "UI/Widget/PFUserWidget.h"

void UPFUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
