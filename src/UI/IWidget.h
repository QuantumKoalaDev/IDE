class IWidget
{
    public:
        virtual ~IWidget() {};

        virtual void draw() = 0;


        // Position in OpenGL coordinates
        // Draw evtl besser in einem zentralen renderer => draw(position, m_vao, m_program)
};