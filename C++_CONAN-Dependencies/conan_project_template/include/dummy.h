#ifndef DUMMY_H_
#define DUMMY_H_

#include <string>

namespace CppTemplate
{

/**
 * @brief The Dummy class used as walking Skeleton class for the unit, spec and feature tests of the template
 */
class Dummy
{
public:
    /**
     * @brief Sp[eechless Dummy
    */
    Dummy () = default;
    /**
     * @brief Dummy who knows how to say hello world
     * @param hello_string 'Hello' in my language
     * @param world_string 'World' in my language
     */
    Dummy (const std::string& hello_string,
           const std::string& world_string);

    /** Say hello world */
    std::string say_hello () const;
    /** Do I know how to speak */
    bool speechless () const;

    private:
    std::string hello_string_{};
    std::string world_string_{};
    bool speechless_{true};
};


} // namespace CppTemplate

#endif //DUMMY_H_
