import { createStore } from "redux";
import rootReducer from "src/store/reducers";

const store = createStore(
    rootReducer,
    window &&
        (window as any).__REDUX_DEVTOOLS_EXTENSION__ &&
        window &&
        (window as any).__REDUX_DEVTOOLS_EXTENSION__()
);

export default store;
