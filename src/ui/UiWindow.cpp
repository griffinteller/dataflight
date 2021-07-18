//
// Created by griff on 7/9/2021.
//

#include "UiWindow.h"
#include "UiContext.h"

void UiWindow::disable()
{
    UiContext::getActiveContext()->removeUiWindow(this);
}

void UiWindow::enable()
{
    UiContext::getActiveContext()->addUiWindow(this);
}

