class ComponentIds{
    const cmpDefault = 01;
    const cmpRenderer2D = 2;
    const cmpCamera = 3;
    const cmpTransform = 4;

}
class Component{
    public:
    Component()=default;
    unsigned int ComponentId;
}

class Transform : public Component{

    protected:
        glm::vec3 m_Position;
        glm::quat m_Rotation;
        glm::vec3 m_Scale;
        Renderable m_Renderable;

    public:
        Transform(){ComponentId = ComponentIds.Transform;}
        Tansform(const glm::vec3 &position,const glm::vec3 &scale, const glm::quat &rot);
        ~Transform();

        Translate(const glm::vec3& axis,float amount);
        Rotate(const glm::vec3& axis,float angle);
        Scale(const glm::vec3& axis,float value);

        
        Matrix4x4 GetModelMatrix();
        
        
        std::vector<Component*> components;
        
};