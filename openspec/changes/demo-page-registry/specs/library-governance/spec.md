## ADDED Requirements

### Requirement: Demo Page Registry

The examples application SHALL define demo pages through a dedicated registry module instead of constructing every page directly in `MainWindow`.

#### Scenario: Main window builds navigation from registry

- **GIVEN** the examples application starts
- **WHEN** `MainWindow` initializes
- **THEN** it SHALL read the ordered demo page definitions
- **AND** add each page title to the navigation list
- **AND** add each constructed widget to the stacked layout

### Requirement: Demo Page Order Stability

The registry MUST preserve the current visible page order.

#### Scenario: Page order is unchanged

- **GIVEN** the current examples application page list
- **WHEN** the registry is used by `MainWindow`
- **THEN** the navigation order SHALL remain `App Bar`, `Auto Complete`, `Avatar`, `Badge`, `Checkbox`, `Circular Progress`, `ComboBox`, `Dialog`, `Divider`, `Drawer`, `Floating Action Button`, `Flat Button`, `Icon Button`, `Menu`, `Progress`, `Radio Button`, `Raised Button`, `ScrollBar`, `Slider`, `Snackbar`, `Steps`, `Tabs`, `Text Field`, `Toggle`

### Requirement: Main Window Shell Responsibility

`MainWindow` MUST only own demo shell layout, navigation, and stack switching concerns.

#### Scenario: Page implementation changes

- **GIVEN** a demo page implementation changes its concrete widget class or construction details
- **WHEN** the change is local to a registered demo page
- **THEN** `MainWindow` SHALL NOT require edits
