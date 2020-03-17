import { combineReducers } from 'redux'
import objectListReducer from "src/store/reducers/objectList";
import objectSelectorReducer from "src/store/reducers/objectSelector";

export default combineReducers({
    objectList: objectListReducer,
    objectSelector: objectSelectorReducer
});
