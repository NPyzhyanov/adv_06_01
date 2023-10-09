#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

int main()
{
    std::string input_string = "Hello, world!!";
    
    std::cout << "[IN]: " << input_string << std::endl;
    
    std::map<char, int> char_frequency_tree; // <char_as_a_key, its_frequency>
    
    bool line_terminator_detected = false;
    char current_char;
    int current_index = 0;
    int max_frequency = 0;
    int emergency_counter = 0;
    while (!line_terminator_detected || emergency_counter < 200)
    {
        emergency_counter++;
        current_char = static_cast<char>(input_string[current_index]);
        if (current_char == '\0')
        {
            line_terminator_detected = true;
            break;
        }
        
        auto it = char_frequency_tree.find(current_char);
        if (it == char_frequency_tree.end())
        {
            char_frequency_tree.insert(std::make_pair(current_char, 1));
        }
        else
        {
            int current_elem_frequency = (++(it->second));
            if (current_elem_frequency > max_frequency)
            {
                max_frequency = current_elem_frequency;
            }
        }
        current_index++;
    }
    
    if (max_frequency < 1)
    {
        std::cerr << "Something wrong happened\n";
        return 1;
    }
    
    std::cout << "[OUT]:\n";
    
    std::vector<std::queue<char>> chars_by_frequencies (max_frequency);
    
    for (auto it = char_frequency_tree.begin(); it != char_frequency_tree.end(); it++)
    {
        char it_first = it->first;
        int it_second = it->second;
        (chars_by_frequencies.at(it_second - 1)).push(it_first);
    }
    
    for (int i = max_frequency - 1; i >= 0; i--)
    {
        while (!(chars_by_frequencies.at(i)).empty())
        {
            std::cout << (chars_by_frequencies.at(i)).front() << ": " << i + 1 << std::endl;
            (chars_by_frequencies.at(i)).pop();
        }
    }
    
    return 0;
}
