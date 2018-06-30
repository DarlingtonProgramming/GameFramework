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
	UpdateTexture(TextureToDraw,true);
}

GameSystem::DrawableImage::DrawableImage(DrawableImage & LeftImage)
{
	UpdateTexture(LeftImage.m_Texture,true);
	this->m_Stretch = LeftImage.m_Stretch;
	DrawableItem::CopyFrom(LeftImage);
	this->m_TempSpriteForPresent = LeftImage.m_TempSpriteForPresent;
}

std::string GameSystem::DrawableImage::getTypeDrawable()
{
	return std::string("DrawableImage");
}

sf::Drawable * GameSystem::DrawableImage::PresentDrawable()
{
	this->UpdateDrawable();
	return &this->m_TempSpriteForPresent;
}

void GameSystem::DrawableImage::UpdateDrawable()
{
	if (this->m_Stretch) {
		sf::Vector2u TextureSize = this->m_Texture.getSize();

		float SpriteXScale = 0.0f, SpriteYScale = 0.0f;
		SpriteXScale = static_cast<float>(this->getWidth()) / static_cast<float>(TextureSize.x);
		SpriteYScale = static_cast<float>(this->getHeight()) / static_cast<float>(TextureSize.y);
		this->m_TempSpriteForPresent.setScale(SpriteXScale, SpriteYScale);
	}
	return;
}

void GameSystem::DrawableImage::UpdateTexture(const sf::Texture & TextureToDraw, bool AdjustSize)
{
	this->m_Texture = TextureToDraw;
	if (AdjustSize) {
		sf::Vector2u NewTextSize = TextureToDraw.getSize();
		DrawableItem::setSize(NewTextSize);
	}
	this->m_TempSpriteForPresent.setTexture(this->m_Texture);
}

void GameSystem::DrawableImage::setStretch(bool Value)
{
	bool NeedUpdateDrawable = Value != this->m_Stretch;
	this->m_Stretch = Value;
	if (NeedUpdateDrawable) {
		this->UpdateDrawable();
	}
}

bool GameSystem::DrawableImage::getStretch()
{
	return this->m_Stretch;
}

void GameSystem::DrawableImage::setRotation(float Angle)
{
	this->m_TempSpriteForPresent.setRotation(Angle);
}

float GameSystem::DrawableImage::getRotation()
{
	return this->m_TempSpriteForPresent.getRotation();
}

void GameSystem::DrawableImage::setColorFilter(sf::Color ColorFilter)
{
	this->m_TempSpriteForPresent.setColor(ColorFilter);
}

sf::Color GameSystem::DrawableImage::getColorFilter()
{
	return this->m_TempSpriteForPresent.getColor();
}

void GameSystem::DrawableImage::setSmooth(bool Smooth)
{
	bool needUpdateSprite = Smooth != this->m_Texture.isSmooth();
	this->m_Texture.setSmooth(Smooth);
	if (needUpdateSprite) {
		this->m_TempSpriteForPresent.setTexture(this->m_Texture);
	}
}

bool GameSystem::DrawableImage::getSmooth()
{
	return this->m_Texture.isSmooth();
}

void GameSystem::DrawableImage::setRepeat(bool Repeat)
{
	bool needUpdateSprite = Repeat != this->m_Texture.isRepeated();
	this->m_Texture.setRepeated(Repeat);
	if (needUpdateSprite) {
		this->m_TempSpriteForPresent.setTexture(this->m_Texture);
	}
}

bool GameSystem::DrawableImage::getRepeat()
{
	return this->m_Texture.isRepeated();
}

void GameSystem::DrawableImage::setPosition(sf::Vector2f Position)
{
	DrawableItem::setPosition(Position);
	this->m_TempSpriteForPresent.setPosition(Position);
}

void GameSystem::DrawableImage::setPosition(float Left, float Top)
{
	DrawableItem::setPosition(Left, Top);
	this->m_TempSpriteForPresent.setPosition(Left, Top);
}

void GameSystem::DrawableImage::setLeft(float Left)
{
	sf::Vector2f OldPos = this->m_TempSpriteForPresent.getPosition();
	DrawableItem::setLeft(Left);
	this->m_TempSpriteForPresent.setPosition(Left, OldPos.y);
}

void GameSystem::DrawableImage::setTop(float Top)
{
	sf::Vector2f OldPos = this->m_TempSpriteForPresent.getPosition();
	DrawableItem::setTop(Top);
	this->m_TempSpriteForPresent.setPosition(OldPos.x, Top);
}

void GameSystem::DrawableImage::setSize(sf::Vector2u Size)
{
	DrawableItem::setSize(Size);
	this->UpdateDrawable();
}

void GameSystem::DrawableImage::setSize(unsigned int Width, unsigned int Height)
{
	DrawableItem::setSize(Width, Height);
	this->UpdateDrawable();
}

void GameSystem::DrawableImage::setWidth(unsigned int Width)
{
	DrawableItem::setWidth(Width);
	this->UpdateDrawable();
}

void GameSystem::DrawableImage::setHeight(unsigned int Height)
{
	DrawableItem::setHeight(Height);
	this->UpdateDrawable();
}

GameSystem::DrawableText::DrawableText(const sf::Font Font, sf::String TextString)
{
	this->setFont(Font);
	this->setTextString(TextString);
}

GameSystem::DrawableText::DrawableText(DrawableText & OldText)
{
	DrawableItem::CopyFrom(OldText);
	this->m_TempTextForPresent = OldText.m_TempTextForPresent;
}

std::string GameSystem::DrawableText::getTypeDrawable()
{
	return std::string("DrawableText");
}

sf::Drawable * GameSystem::DrawableText::PresentDrawable()
{
	this->UpdateDrawable();
	return &this->m_TempTextForPresent;
}

void GameSystem::DrawableText::UpdateDrawable()
{
	return;
}

void GameSystem::DrawableText::setStyle(sf::Uint32 Style)
{
	this->m_TempTextForPresent.setStyle(Style);
}

sf::Uint32 GameSystem::DrawableText::getStyle()
{
	return this->m_TempTextForPresent.getStyle();
}

void GameSystem::DrawableText::setFont(sf::Font font)
{
	this->m_TempTextForPresent.setFont(font);
}

sf::Font GameSystem::DrawableText::getFont()
{
	return (*this->m_TempTextForPresent.getFont());
}

void GameSystem::DrawableText::setTextString(sf::String TextString)
{
	this->m_TempTextForPresent.setString(TextString);
}

sf::String GameSystem::DrawableText::getTextString()
{
	return this->m_TempTextForPresent.getString();
}

void GameSystem::DrawableText::setFontSize(unsigned int SizeInPixel)
{
	this->m_TempTextForPresent.setCharacterSize(SizeInPixel);
}

unsigned int GameSystem::DrawableText::getFontSize()
{
	return this->m_TempTextForPresent.getCharacterSize();
}

void GameSystem::DrawableText::setOutlineThickness(float Thickness)
{
	this->m_TempTextForPresent.setOutlineThickness(Thickness);
}

float GameSystem::DrawableText::getOutlineThickness()
{
	return this->m_TempTextForPresent.getOutlineThickness();
}

void GameSystem::DrawableText::setFillColor(sf::Color FillColor)
{
	this->m_TempTextForPresent.setFillColor(FillColor);
}

sf::Color GameSystem::DrawableText::getFillColor()
{
	return this->m_TempTextForPresent.getFillColor();
}

void GameSystem::DrawableText::setOutLineColor(sf::Color OutLineColor)
{
	this->m_TempTextForPresent.setOutlineColor(OutLineColor);
}

sf::Color GameSystem::DrawableText::getOutLineColor()
{
	return this->m_TempTextForPresent.getOutlineColor();
}

void GameSystem::DrawableText::setLetterSpacing(float SpacingFactor)
{
	this->m_TempTextForPresent.setLetterSpacing(SpacingFactor);
}

float GameSystem::DrawableText::getLetterSpacing()
{
	return this->m_TempTextForPresent.getLetterSpacing();
}

void GameSystem::DrawableText::setLineSpacing(float SpacingFactor)
{
	this->m_TempTextForPresent.setLineSpacing(SpacingFactor);
}

float GameSystem::DrawableText::getLineSpacing()
{
	return this->m_TempTextForPresent.getLineSpacing();
}

void GameSystem::DrawableText::setPosition(sf::Vector2f Position)
{
	DrawableItem::setPosition(Position);
	this->m_TempTextForPresent.setPosition(Position);
}

void GameSystem::DrawableText::setPosition(float Left, float Top)
{
	DrawableItem::setPosition(Left, Top);
	this->m_TempTextForPresent.setPosition(Left, Top);
}

void GameSystem::DrawableText::setLeft(float Left)
{
	DrawableItem::setLeft(Left);
	sf::Vector2f OldPos = this->m_TempTextForPresent.getPosition();
	this->m_TempTextForPresent.setPosition(Left, OldPos.y);
}

void GameSystem::DrawableText::setTop(float Top)
{
	DrawableItem::setTop(Top);
	sf::Vector2f OldPos = this->m_TempTextForPresent.getPosition();
	this->m_TempTextForPresent.setPosition(OldPos.x, Top);
}

sf::Vector2u GameSystem::DrawableText::getSize()
{
	sf::FloatRect MyGlobalRect = this->m_TempTextForPresent.getGlobalBounds();
	return sf::Vector2u(static_cast<unsigned int>(MyGlobalRect.width),static_cast<unsigned int>(MyGlobalRect.height));
}

unsigned int GameSystem::DrawableText::getWidth()
{
	sf::FloatRect MyGlobalRect = this->m_TempTextForPresent.getGlobalBounds();
	return static_cast<unsigned int>(MyGlobalRect.width);
}

unsigned int GameSystem::DrawableText::getHeight()
{
	sf::FloatRect MyGlobalRect = this->m_TempTextForPresent.getGlobalBounds();
	return static_cast<unsigned int>(MyGlobalRect.height);
}

GameSystem::DrawableImageSerie::DrawableImageSerie(const std::vector<std::pair<sf::Texture, float>>& TexturesToDraw)
{
	this->UpdateTextures(TexturesToDraw,true);
}

GameSystem::DrawableImageSerie::DrawableImageSerie(DrawableImageSerie & OldImageSerie)
{
	DrawableItem::CopyFrom(OldImageSerie);
	this->m_DeviateTime = OldImageSerie.m_DeviateTime;
	this->m_LockedTime = OldImageSerie.m_LockedTime;
	this->m_isClockLocked = OldImageSerie.m_isClockLocked;
	this->m_SharedClock = OldImageSerie.m_SharedClock;
	this->m_Textures = OldImageSerie.m_Textures;
	this->m_TempSpriteForPresent = OldImageSerie.m_TempSpriteForPresent;
	this->m_Stretch = OldImageSerie.m_Stretch;
	this->m_Smooth = OldImageSerie.m_Smooth;
	this->m_Repeat = OldImageSerie.m_Repeat;
}

std::string GameSystem::DrawableImageSerie::getTypeDrawable()
{
	return "DrawableImageSerie";
}

sf::Drawable * GameSystem::DrawableImageSerie::PresentDrawable()
{
	this->UpdateDrawable();
	return &this->m_TempSpriteForPresent;
}
void GameSystem::DrawableImageSerie::UpdateDrawable()
{
	sf::Texture TempDisplayTexture;
	float nowTimeF = 0.0f;
	if (!this->m_isClockLocked) {
		sf::Time nowTime = this->m_SharedClock.getElapsedTime();
		nowTimeF = nowTime.asSeconds() + this->m_DeviateTime;
	}
	else {
		nowTimeF = this->m_LockedTime;
	}
	unsigned int Order = 0U;
	for (auto i = this->m_Textures.begin(); i != this->m_Textures.end(); i++) {
		if ((*i).second <= nowTimeF) {
			nowTimeF -= (*i).second;
			Order++;
		}
		else {
			break;
		}
	}
	if (Order > this->m_Textures.size() - 1) {
		//Overtime, refresh cycle
		if (this->m_isClockLocked) {
			this->m_LockedTime = nowTimeF;
		}
		else {
			this->m_DeviateTime = nowTimeF;
			this->m_SharedClock.restart();
		}
		return this->UpdateDrawable();
	}
	
	TempDisplayTexture = this->m_Textures[Order].first;
	TempDisplayTexture.setRepeated(this->m_Repeat);
	TempDisplayTexture.setSmooth(this->m_Smooth);
	
	this->m_TempSpriteForPresent.setTexture(TempDisplayTexture);
	if (this->m_Stretch) {
		sf::Vector2u TextureSize = TempDisplayTexture.getSize();

		float SpriteXScale = 0.0f, SpriteYScale = 0.0f;
		SpriteXScale = static_cast<float>(this->getWidth()) / static_cast<float>(TextureSize.x);
		SpriteYScale = static_cast<float>(this->getHeight()) / static_cast<float>(TextureSize.y);
		this->m_TempSpriteForPresent.setScale(SpriteXScale, SpriteYScale);
	}
	return;
}
void GameSystem::DrawableImageSerie::UpdateTextures(const std::vector<std::pair<sf::Texture, float>>& TexturesToDraw, bool AdjustSize)
{
	this->m_Textures = TexturesToDraw;
	if (AdjustSize) {
		sf::Vector2u NewTextSize = TexturesToDraw[0].first.getSize();
		DrawableItem::setSize(NewTextSize);
	}
	this->m_LockedTime = 0.0f;
	this->m_DeviateTime = 0.0f;
	this->m_SharedClock.restart();
}
void GameSystem::DrawableImageSerie::setStretch(bool Value)
{
	bool needUpdateImageSerie = Value != this->m_Stretch;
	this->m_Stretch = Value;
	if (needUpdateImageSerie) {
		this->UpdateDrawable();
	}
}
bool GameSystem::DrawableImageSerie::getStretch()
{
	return this->m_Stretch;
}
void GameSystem::DrawableImageSerie::setPosition(sf::Vector2f Position)
{
	DrawableItem::setPosition(Position);
	this->m_TempSpriteForPresent.setPosition(Position);
}

void GameSystem::DrawableImageSerie::setPosition(float Left, float Top)
{
	DrawableItem::setPosition(Left, Top);
	this->m_TempSpriteForPresent.setPosition(Left, Top);
}

void GameSystem::DrawableImageSerie::setLeft(float Left)
{
	sf::Vector2f OldPos = this->m_TempSpriteForPresent.getPosition();
	DrawableItem::setLeft(Left);
	this->m_TempSpriteForPresent.setPosition(Left, OldPos.y);
}

void GameSystem::DrawableImageSerie::setTop(float Top)
{
	sf::Vector2f OldPos = this->m_TempSpriteForPresent.getPosition();
	DrawableItem::setTop(Top);
	this->m_TempSpriteForPresent.setPosition(OldPos.x, Top);
}

void GameSystem::DrawableImageSerie::setSize(sf::Vector2u Size)
{
	DrawableItem::setSize(Size);
	this->UpdateDrawable();
}

void GameSystem::DrawableImageSerie::setSize(unsigned int Width, unsigned int Height)
{
	DrawableItem::setSize(Width, Height);
	this->UpdateDrawable();
}

void GameSystem::DrawableImageSerie::setWidth(unsigned int Width)
{
	DrawableItem::setWidth(Width);
	this->UpdateDrawable();
}

void GameSystem::DrawableImageSerie::setHeight(unsigned int Height)
{
	DrawableItem::setHeight(Height);
	this->UpdateDrawable();
}

void GameSystem::DrawableImageSerie::setRotation(float Angle)
{
	this->m_TempSpriteForPresent.setRotation(Angle);
}

float GameSystem::DrawableImageSerie::getRotation()
{
	return this->m_TempSpriteForPresent.getRotation();
}

void GameSystem::DrawableImageSerie::setColorFilter(sf::Color ColorFilter)
{
	this->m_TempSpriteForPresent.setColor(ColorFilter);
}

sf::Color GameSystem::DrawableImageSerie::getColorFilter()
{
	return this->m_TempSpriteForPresent.getColor();
}

void GameSystem::DrawableImageSerie::setSmooth(bool Smooth)
{
	bool needUpdateDrawableSerie = this->m_Smooth != Smooth;
	this->m_Smooth = Smooth;
	if (needUpdateDrawableSerie) {
		this->UpdateDrawable();
	}
}

bool GameSystem::DrawableImageSerie::getSmooth()
{
	return this->m_Smooth;
}

void GameSystem::DrawableImageSerie::setRepeat(bool Repeat)
{
	bool needUpdateDrawableSerie = this->m_Repeat != Repeat;
	this->m_Repeat = Repeat;
	if (needUpdateDrawableSerie) {
		this->UpdateDrawable();
	}
}

bool GameSystem::DrawableImageSerie::getRepeat()
{
	return this->m_Repeat;
}
