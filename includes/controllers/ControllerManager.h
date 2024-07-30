class ControllerManager {

    public:

        static ControllerManager& GetInstance() {
            static ControllerManager instance;
            return instance;
        }

        ControllerManager(const ControllerManager&) = delete;
        ControllerManager& operator=(const ControllerManager&) = delete;
        std::vector<sf::Text> GetJoystickButtons(unsigned int joystickIndex);
        std::string GetButtonState(bool isPressed);

    private:
        ControllerManager() = default;
        ~ControllerManager() = default;
};
