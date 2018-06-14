#include "GameSystemDrawable.h"

void GameSystem::DrawableItem::deleteItem()
{
	//标记此项为删除项, Scene会在垃圾删除周期删除此Item.
	this->m_WillDeleteNextCycle = true;
}

void GameSystem::DrawableItem::setClickEventHandler(DrawableClickEvent Handler)
{
	this->m_ClickEvent = Handler;
}

void GameSystem::DrawableItem::setMouseMoveEventHandler(DrawableMouseMoveEvent Handler)
{
	this->m_MouseMoveEvent = Handler;
}

void GameSystem::DrawableItem::setMouseDownEventHandler(DrawableMouseDownEvent Handler)
{
	this->m_MouseDownEvent = Handler;
}

void GameSystem::DrawableItem::setMouseUpEventHandler(DrawableMouseUpEvent Handler)
{
	this->m_MouseUpEvent = Handler;
}

void GameSystem::DrawableItem::setMouseEnterEventHandler(DrawableMouseEnterEvent Handler)
{
	this->m_MouseEnterEvent = Handler;
}

void GameSystem::DrawableItem::setMouseLeaveEventHandler(DrawableMouseLeaveEvent Handler)
{
	this->m_MouseLeaveEvent = Handler;
}

void GameSystem::DrawableItem::setPosition(sf::Vector2f Position)
{
	this->Left = Position.x;
	this->Top = Position.y;
}

void GameSystem::DrawableItem::setPosition(float Left, float Top)
{
	this->Left = Left;
	this->Top = Top;
}

void GameSystem::DrawableItem::setLeft(float Left)
{
	this->Left = Left;
}

void GameSystem::DrawableItem::setTop(float Top)
{
	this->Top = Top;
}

float GameSystem::DrawableItem::getLeft()
{
	return this->Left;
}

float GameSystem::DrawableItem::getTop()
{
	return this->Left;
}

void GameSystem::DrawableItem::setZIndex(int zIndex)
{
	this->zIndex = zIndex;
}

int GameSystem::DrawableItem::getZIndex()
{
	return this->zIndex;
}

bool GameSystem::DrawableItem::getVisibility()
{
	return this->isVisible;
}

void GameSystem::DrawableItem::setVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

GameSystem::Activity * GameSystem::DrawableItem::GetFather()
{
	return this->m_FatherClass;
}

sf::Vector2f GameSystem::DrawableItem::getPosition()
{
	return sf::Vector2f(this->Left,this->Top);
}

void GameSystem::DrawableItem::setSize(sf::Vector2u Size)
{
	this->Width = Size.x;
	this->Height = Size.y;
}

void GameSystem::DrawableItem::setSize(unsigned int Width, unsigned int Height)
{
	this->Width = Width;
	this->Height = Height;
}

void GameSystem::DrawableItem::setWidth(unsigned int Width)
{
	this->Width = Width;
}

void GameSystem::DrawableItem::setHeight(unsigned int Height)
{
	this->Height = Height;
}

sf::Vector2u GameSystem::DrawableItem::getSize()
{
	return sf::Vector2u(this->Width,this->Height);
}

unsigned int GameSystem::DrawableItem::getWidth()
{
	return this->Width;
}

unsigned int GameSystem::DrawableItem::getHeight()
{
	return this->Height;
}

void GameSystem::DrawableItem::call_OnDrawableClickEvent(int X, int Y)
{
	if (this->m_ClickEvent != NULL) {
		this->m_ClickEvent(X, Y, this);
	}
}

void GameSystem::DrawableItem::call_OnDrawableMouseMoveEvent(int X, int Y)
{
	if (this->m_MouseMoveEvent != NULL) {
		this->m_MouseMoveEvent(X, Y, this);
	}
}

void GameSystem::DrawableItem::call_OnDrawableMouseDownEvent(int X, int Y)
{
	if (this->m_MouseDownEvent != NULL) {
		this->m_MouseDownEvent(X, Y, this);
	}
}

void GameSystem::DrawableItem::call_OnDrawableMouseUpEvent(int X, int Y)
{
	if (this->m_MouseUpEvent != NULL) {
		this->m_MouseUpEvent(X, Y, this);
	}
}

void GameSystem::DrawableItem::call_OnDrawableMouseEnterEvent(int X, int Y)
{
	if (this->m_MouseEnterEvent != NULL) {
		this->m_MouseEnterEvent(X, Y, this);
	}
}

void GameSystem::DrawableItem::call_OnDrawableMouseLeaveEvent()
{
	if (this->m_MouseLeaveEvent != NULL) {
		this->m_MouseLeaveEvent(this);
	}
}

void GameSystem::DrawableItem::CopyFrom(DrawableItem & OldItem)
{
	this->m_WillDeleteNextCycle = false;
	this->Top = OldItem.Top;
	this->Left = OldItem.Left;
	this->Width = OldItem.Width;
	this->Height = OldItem.Height;
	this->zIndex = OldItem.zIndex;
	this->isVisible = OldItem.isVisible;
	this->m_FatherClass = OldItem.m_FatherClass;
	this->m_ClickEvent = OldItem.m_ClickEvent;
	this->m_MouseMoveEvent = OldItem.m_MouseMoveEvent;
	this->m_MouseDownEvent = OldItem.m_MouseDownEvent;
	this->m_MouseUpEvent = OldItem.m_MouseUpEvent;
	this->m_MouseEnterEvent = OldItem.m_MouseEnterEvent;
	this->m_MouseLeaveEvent = OldItem.m_MouseLeaveEvent;
}

GameSystem::DrawableImage::DrawableImage(const sf::Texture &TextureToDraw)
{
	this->m_ColorFilter = sf::Color(255, 255, 255, 255);
	UpdateTexture(TextureToDraw,true);
}

GameSystem::DrawableImage::DrawableImage(DrawableImage & LeftImage)
{
	this->m_ColorFilter = sf::Color(255, 255, 255, 255);
	UpdateTexture(LeftImage.m_Texture,true);
	this->m_Stretch = LeftImage.m_Stretch;
	this->m_Rotation = LeftImage.m_Rotation;
	this->m_ColorFilter = LeftImage.m_ColorFilter;
	this->m_Smooth = LeftImage.m_Smooth;
	DrawableItem::CopyFrom(LeftImage);
}

std::string GameSystem::DrawableImage::getTypeDrawable()
{
	return std::string("DrawableImage");
}

sf::Drawable * GameSystem::DrawableImage::PresentDrawable()
{
	sf::Vector2u TextureSize = this->m_Texture.getSize();

	this->m_Texture.setSmooth(this->m_Smooth);

	this->m_TempSpriteForPresent.setTexture(this->m_Texture);
	float SpriteXScale = 0.0f, SpriteYScale = 0.0f;
	SpriteXScale = static_cast<float>(this->getWidth()) / static_cast<float>(TextureSize.x);
	SpriteYScale = static_cast<float>(this->getHeight()) / static_cast<float>(TextureSize.y);
	if (this->m_Stretch) {
		this->m_TempSpriteForPresent.setScale(SpriteXScale, SpriteYScale);
	}
	this->m_TempSpriteForPresent.setRotation(this->m_Rotation);
	this->m_TempSpriteForPresent.setColor(this->m_ColorFilter);

	return &this->m_TempSpriteForPresent;
}

void GameSystem::DrawableImage::UpdateTexture(const sf::Texture & TextureToDraw, bool AdjustSize)
{
	sf::Vector2u NewTextSize = TextureToDraw.getSize();
	this->m_Texture.create(NewTextSize.x, NewTextSize.y);
	this->m_Texture.update(TextureToDraw);
	if (AdjustSize) {
		DrawableItem::setSize(NewTextSize);
	}
}

void GameSystem::DrawableImage::setStretch(bool Value)
{
	this->m_Stretch = Value;
}

bool GameSystem::DrawableImage::getStretch()
{
	return this->m_Stretch;
}

void GameSystem::DrawableImage::setRotation(float Angle)
{
	this->m_Rotation = Angle;
}

float GameSystem::DrawableImage::getRotation()
{
	return this->m_Rotation;
}

void GameSystem::DrawableImage::setColorFilter(sf::Color ColorFilter)
{
	this->m_ColorFilter = ColorFilter;
}

sf::Color GameSystem::DrawableImage::getColorFilter()
{
	return this->m_ColorFilter;
}

void GameSystem::DrawableImage::setSmooth(bool Smooth)
{
	this->m_Smooth = Smooth;
}

bool GameSystem::DrawableImage::getSmooth()
{
	return this->m_Smooth;
}
