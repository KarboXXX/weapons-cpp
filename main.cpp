#include <iostream>
#include <string>
#include <assert.h>
#include <stdio.h>

class Magazine {
    private:
        int ammo;
        int capacity;
    public:
        Magazine(int ammo, int capacity) {
            if (capacity >= 90)
                capacity = 90;
            
            if (ammo >= capacity)
                ammo = capacity;
            
            this->ammo = ammo;
            this->capacity = capacity;
        }

        int use(int howMuch = 1) {
            if (howMuch < 1) { return 0; }

            if (this->ammo <= 0) { return 0; }
            
            if (howMuch >= this->ammo) {
                this->ammo = 0;
                return howMuch;
            }

            this->ammo -= howMuch;
            return howMuch;
        }

        int load(int capac) {
            int load;
            
            if (capac < this->ammo) load = this->ammo - capac;
            else load = this->ammo;

            return this->use(load);
        }

        int getCapacity() { return this->capacity; }
        int getUsage() { return this->ammo; }
};

class Weapon {
    private:
        int ammo;
        int maxAmmo;
        int damage;
        int range;
    public:
        Weapon(int ammo, int maxAmmo, int damage, int range) {
            if (maxAmmo >= 30)
                maxAmmo = 30;
            
            if (ammo > maxAmmo)
                ammo = maxAmmo;
            
            if (range >= 700)
                range = 700;
            
            this->ammo = ammo;
            this->maxAmmo = maxAmmo;
            this->damage = damage;
            this->range = range;
        }

        void fire(int times = 1) {
            for (int i=1; i<=times; i++) {
                if (this->ammo <= 0) {
                    printf("You're out of ammo.");
                    break;
                }
                printf("BAAAAM +%d ", damage);
                this->ammo -= 1;
            }
            printf("\n");
        }

        int fire(int times, bool forceReload, Magazine *magazine) {
            int i = 1;
            for (i=1; i<=times; i++) {
                if (this->ammo <= 0) {
                    int reloadSucessfull = this->reload(forceReload, magazine);
                    if (reloadSucessfull == 0) { break; } else { printf(" - (Reloaded.) - "); }
                }
                printf("BAAAAM +%d ", damage);
                this->ammo -= 1;
            }
            printf("\n");
            return (i - 1);
        }

        int reload(bool force, Magazine *magazine) {
            int loaded = magazine->load(this->getAmmoCapacity());
            this->ammo += loaded;
            if (loaded > 0) return 1;
            else return 0;
        }

        int getAmmoCapacity() { return this->maxAmmo; }
        int getAmmoLeft() { return this->ammo; }
        int getWeaponRange() { return this->range; }
        int getDamage() { return this->damage; }
};

int main(int argc, char *argv[]) {
    int times;
    try { times = std::stoi(argv[1]); } catch(const std::exception& e) { return 1; }

    Weapon pistol(30, 30, 50, 100);
    Magazine mag(90, 90);
    int fired;

    printf("ammo: %d\nnow, firing %d times.\n\n", pistol.getAmmoLeft(), times);
    fired = pistol.fire(times, false, &mag);
    printf("\nammo: %d\nmag usage left:%d\nfired: %d\n", pistol.getAmmoLeft(), mag.getUsage(), fired);
}