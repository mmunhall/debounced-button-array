const int MOMENTARY_PINS[] = {2, 3, 4, 5, 6, 7};
const long BOUNCE_DELAY = 50;
const int NUM_BUTTONS = sizeof(MOMENTARY_PINS)/sizeof(int);

int BUTTON_STATES[NUM_BUTTONS];
int LAST_BUTTON_STATES[NUM_BUTTONS];
long LAST_BUTTON_DEBOUNCE_TIMES[NUM_BUTTONS];

void setup() {
  Serial.begin(9600);
  for (int i=0; i<NUM_BUTTONS; i++) {
    pinMode(MOMENTARY_PINS[i], INPUT_PULLUP);
    BUTTON_STATES[i] = HIGH;
    LAST_BUTTON_STATES[i] = HIGH;
    LAST_BUTTON_DEBOUNCE_TIMES[i] = 0;
  }
}

void loop() {
  for (int i=0; i<NUM_BUTTONS; i++) {
    int reading = digitalRead(MOMENTARY_PINS[i]);
    
    if (reading != LAST_BUTTON_STATES[i]) {
      LAST_BUTTON_DEBOUNCE_TIMES[i] = millis();
    } 
  
    if ((millis() - LAST_BUTTON_DEBOUNCE_TIMES[i]) > BOUNCE_DELAY) {
      if (reading != BUTTON_STATES[i]) {
        BUTTON_STATES[i] = reading;
  
        if (BUTTON_STATES[i] == LOW) {
          Serial.print("Button pressed: ");
          Serial.println(i);
        }
      }
    }
    
    LAST_BUTTON_STATES[i] = reading;
  }
}
