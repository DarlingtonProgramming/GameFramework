#ifndef __GAMEFRAMEWORK_GAMESYSTEMDRAWABLE_FILE__
	#define __GAMEFRAMEWORK_GAMESYSTEMDRAWABLE_FILE__
	#include <SFML/Graphics.hpp>
	namespace GameSystem {
		class Activity; //事先声明Activity类.
		class DrawableItem; //事先声明DrawableItem类, 可以在函数回调中直接送回DrawableItem的指针
		typedef void(*DrawableClickEvent)(int, int, DrawableItem*);
		typedef void(*DrawableMouseMoveEvent)(int, int, DrawableItem*);
		typedef void(*DrawableMouseDownEvent)(int, int, DrawableItem*);
		typedef void(*DrawableMouseUpEvent)(int, int, DrawableItem*);
		typedef void(*DrawableMouseEnterEvent)(int, int, DrawableItem*);
		typedef void(*DrawableMouseLeaveEvent)(DrawableItem*);
		
		class DrawableItem {
		friend class Activity;
		private:
			DrawableClickEvent m_ClickEvent = NULL;
			DrawableMouseMoveEvent m_MouseMoveEvent = NULL;
			DrawableMouseDownEvent m_MouseDownEvent = NULL;
			DrawableMouseUpEvent m_MouseUpEvent = NULL;
			DrawableMouseEnterEvent m_MouseEnterEvent = NULL;
			DrawableMouseLeaveEvent m_MouseLeaveEvent = NULL;
		protected:
			void CopyFrom(DrawableItem& OldItem);
			bool m_WillDeleteNextCycle = false;
			float Top = 0.0f;
			float Left = 0.0f;
			unsigned int Width = 0U;
			unsigned int Height = 0U;
			int zIndex = 0;
			bool isVisible = true;
			Activity* m_FatherClass = NULL;
			void call_OnDrawableClickEvent(int X, int Y);
			void call_OnDrawableMouseMoveEvent(int X, int Y);
			void call_OnDrawableMouseDownEvent(int X, int Y);
			void call_OnDrawableMouseUpEvent(int X, int Y);
			void call_OnDrawableMouseEnterEvent(int X, int Y);
			void call_OnDrawableMouseLeaveEvent();
		public:
			virtual std::string getTypeDrawable() = 0;
			virtual sf::Drawable* PresentDrawable() = 0;
			void deleteItem();
			void setClickEventHandler(DrawableClickEvent Handler);
			void setMouseMoveEventHandler(DrawableMouseMoveEvent Handler);
			void setMouseDownEventHandler(DrawableMouseDownEvent Handler);
			void setMouseUpEventHandler(DrawableMouseUpEvent Handler);
			void setMouseEnterEventHandler(DrawableMouseEnterEvent Handler);
			void setMouseLeaveEventHandler(DrawableMouseLeaveEvent Handler);
			virtual void setPosition(sf::Vector2f Position);
			virtual void setPosition(float Left, float Top);
			virtual void setLeft(float Left);
			virtual void setTop(float Top);
			float getLeft();
			float getTop();
			void setZIndex(int zIndex);
			int getZIndex();
			bool getVisibility();
			void setVisible(bool isVisible);
			Activity* GetFather();
			sf::Vector2f getPosition();
			virtual void setSize(sf::Vector2u Size);
			virtual void setSize(unsigned int Width, unsigned int Height);
			virtual void setWidth(unsigned int Width);
			virtual void setHeight(unsigned int Height);
			sf::Vector2u getSize();
			unsigned int getWidth();
			unsigned int getHeight();
		};
		
		class DrawableImage : public DrawableItem {
		private:

		protected:
			sf::Texture m_Texture;
			sf::Sprite m_TempSpriteForPresent;
			bool m_Stretch = true;
			float m_Rotation = 0.0f;
			sf::Color m_ColorFilter;
			bool m_Smooth = true;
		public:
			DrawableImage(const sf::Texture &TextureToDraw);
			DrawableImage(DrawableImage &LeftImage);
			std::string getTypeDrawable();
			sf::Drawable* PresentDrawable();
			
			void UpdateTexture(const sf::Texture& TextureToDraw, bool AdjustSize = false);

			void setStretch(bool Value);
			bool getStretch();

			void setRotation(float Angle);
			float getRotation();

			void setColorFilter(sf::Color ColorFilter);
			sf::Color getColorFilter();

			void setSmooth(bool Smooth);
			bool getSmooth();
		};
		
	}
	
#endif