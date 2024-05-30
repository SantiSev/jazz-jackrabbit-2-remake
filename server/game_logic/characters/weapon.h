#ifndef TP_FINAL_WEAPON_H
#define TP_FINAL_WEAPON_H

#include <cstdio>
class Weapon {
private:
    size_t weapon_name = 0;
    size_t ammo = 0;
    bool is_empty = true;

public:
    Weapon();
    ~Weapon();
    void set_weapon_name(size_t weapon_name);
    size_t get_weapon_name () const;
    void set_ammo(size_t new_ammo);
    void add_ammo(size_t added_ammo);
    size_t get_ammo() const;
    void set_is_empty(bool is_weapon_empty);
    bool is_weapon_empty() const;
    void decrease_ammo();
};

#endif
