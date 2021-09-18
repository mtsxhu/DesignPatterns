class Framebuffer
{
public:
  Framebuffer()  = default;

  void clear()
  {
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
      m_pixels[i] = 	0xFFFFFF;
    }
  }

  void draw(int x, int y,char color)
  {
    m_pixels[WIDTH * y + x] = color;
  }

  const char* getPixels()
  {
    return m_pixels;
  }

private:
  static constexpr int WIDTH = 160;
  static constexpr int HEIGHT = 120;
  char m_pixels[WIDTH * HEIGHT];
};

class Scene
{
public:
  Scene()
  {
      m_current = new Framebuffer();
      m_next = new Framebuffer();
  }

  void draw(int x,int y,char color )
  {
    m_next->clear();

    // 由于读写缓冲区不同,因此这三次draw操作相当于是原子操作
    m_next->draw(x, y,color);
    m_next->draw(x+1, y+1,color);
    m_next->draw(x+2, y+2,color);

    swap();
  }

  Framebuffer& getBuffer() { return *m_current; }

private:
  void swap()
  {
    Framebuffer* temp = m_current;
    m_current = m_next;
    m_next = temp;
  }

  Framebuffer* m_current;
  Framebuffer* m_next;
};