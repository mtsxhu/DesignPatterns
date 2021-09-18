class Actor
{
public:
  Actor() : m_currentSlapped(false) {}

  virtual ~Actor() {}
  virtual void update() = 0;

  void swap()
  {
    // 交换缓冲区
    m_currentSlapped = m_nextSlapped;

    // 清空新的“下一个”缓冲区。.
    m_nextSlapped = false;
  }

  void slap()       { m_nextSlapped = true; }
  bool wasSlapped() { return m_currentSlapped; }

private:
  bool m_currentSlapped;
  bool m_nextSlapped;
};

class Comedian : public Actor
{
public:
  void face(Actor* actor) { m_facing = actor; }

  virtual void update()
  {
    if (wasSlapped()){
        m_facing->slap();
    } 
  }

private:
  Actor* m_facing;
};

class Stage
{
public:
  void add(Actor* actor, int index)
  {
    m_actorList[index] = actor;
  }

/*
    角色无论在舞台数组中如何排列，都会保持相同的行为。
    无论外部的代码如何调用，所有的角色在一帧内同时更新。
*/
  void update()
  {
      // update和swap操作分开
    for (int i = 0; i < NUM_ACTORS; i++)
    {
        m_actorList[i]->update();
    }

    for (int i = 0; i < NUM_ACTORS; i++)
    {
        m_actorList[i]->swap();
    }
  }

private:
  static const int NUM_ACTORS = 3;

  Actor* m_actorList[NUM_ACTORS];
};