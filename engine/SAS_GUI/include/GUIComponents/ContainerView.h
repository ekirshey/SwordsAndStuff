namespace SAS_GUI {
	struct ContainerView {
		SDL_Rect cliprect;
		int verticalSlotSeparation;
		int horizontalSlotSeparation;
		int slotWidth;
		int slotHeight;
		int maxHorizontalSlots;
		int maxVerticalSlots;
		std::string texture;

		ContainerView(SDL_Rect clip, int vertsep, int horzsep, int slotwidth, int slotheight, 
			int maxhorz, int maxvert, std::string bg) 
			: cliprect(clip)
			, verticalSlotSeparation(vertsep)
			, horizontalSlotSeparation(horzsep)
			, slotWidth(slotwidth)
			, slotHeight(slotheight)
			, maxHorizontalSlots(maxhorz)
			, maxVerticalSlots(maxvert)
			, texture(bg)
		{

		}
	};
}